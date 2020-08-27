# B&G Fastnet Driver

## 01. Introduction
Fastnet was introduced with the Hydra/Hercules 390 series of B&G processors
in the late 1980s. It is a two-wire half-duplex multi-drop bus, electrically
similar to RS-485 or CANBUS and can be interfaced with either an RS-485 or
CANBUS driver. It operates at 28.8k 8-bits, odd parity, two stop bits (8N2).

## 02. Frame Layout
Fastnet frames are variable length and there is no indication that a new
frame has started. In order to sync with the data stream, the easiest thing
is to wait for an `FFh` byte and then try to decode that byte and the next
four as a frame header. If that works, you're probably synced. But maybe
not. There may be a message that can be sent requesting a synchronization
frame, but I haven't discovered one yet.

00           | 01     | 02          | 03      | 04              | 05 - nn | nn + 1
-------------|--------|-------------|---------|-----------------|---------|---------------
 Destination | Source | Data Length | Command | Header Checksum | Data    | Data Checksum

I don't know for sure, but I suspect the longest a frame can be is 255
bytes, which means that the longest the data section could be is 255 - 6 or
249 bytes. It's possible that the frame could be as long as 261 bytes, but I
don't know how the B&G devices process the data.

Some commands take no parameters, in which case byte 2 is `00h` and there
is no data or data checksum. Many commands take a variable number of bytes.

## 03. Node Addresses

### Individual Device Addresses
- `01h` - Depth CPU (e.g. Hydra, H1000 depth interface)
- `05h` - Wind CPU (e.g. Hercules, H1000 wind interface)
- `09h` - Performance CPU (e.g. Performance addon, NMEA interface)
- `0Dh` - Expansion module 1
- `OEh` - Expansion module 2
- `0Fh` - Halcyon CPU
- `10h` - H2000 Gyro compass interface
- `12h` - Autopilot (ACP) gyro compass
- `20h`-`2Fh`- Full-function displays (FFD)
- `30h`-`3Fh`- Halcyon FFDs
- `40h`-`4Fh` - 20/20 displays
- `50h`-`5Fh` - Pilot FFDs
- `60h`-`6Eh` - NMEA capable FFDs
- `6Fh` - Wireless interface
- `70h`-`7Fh` - Loadcell amplifiers
- `80h` - Tank sensor

### Group Addresses
- `FAh` - All 20/20 displays
- `FBh` - All Halcyon FFDs
- `FCh` - All Pilot FFDs
- `FDh` - All CPUs
- `FEh` - All FFDs
- `FFh` - All devices (broadcast)

## 04. Commands

This is not all of the commands, just the ones implemented by this software.

Command | Description                  | Bytes
--------|------------------------------|-----------
`01h` | Send data. Most common command | Variable
`C9h` | Set backlight                  | 2
`F6h` | Chnage page                    | 2
`F7h` | Configure current page         | Variable
`F8h` | Save page configuration        |

### `01h` - Send Data

01 | 02 | 03 - nn
---|----|----|-------
Channel | Display format | Value

The payload of the send data command is fairly complex. Bytes 1 to nn can
repeat to send multiple values. Sometimes the format byte and value bytes
overlap.

### `02h` - Channel Label

   01   |  02  | 03 - 12
--------|------|---------
Channel | Node | Label

Channel is the channel to label, e.g. `1eh`, Sea Temp °F. Node is sending
node for the chosen channel. This byte is optional. If it's not there, then
the default node is chosen. If it is supplied, you may not see a change on
the display as the alternate source is probably not configured in the
display device.

The label is ASCII. Valid characters are numbers (0-9), uppercase letters
(A-Z) and the symbols dash (-), solidus (/), period (.), comma (,) and
percent (%). Period is represented as the bottom left segment of the LCD
character, comma is the middle right segment of the LCD character. Percent
is interpreted as degree (°). It's questionable whether period and comma are
actually valid characters or just an accident.

FFDs respond to this immediately, but 20/20 displays do not respond until
they receive data on the channel.

### `03h` - Send ASCII Text

This command is for sending ASCII text on the bus. As far as I know, the only
use for this is to send latitude and longitude on channel `47h`. See section
below for the format of the string.

### `C8h` - Power Off

This command will power off the whole system. It takes no payload.

### `C9h` - Set Backlight

The FFDs will send the following for backlight values. However, the displays
will respond to any level between `00h` and `07h`.`

01 | 02
----|-------
Light level | `20h`

Possible light level values are:
- `0` - Off
- `1` - Low
- `2` - Medium
- `4` - High

The second byte is always `20h`.

### `F6h` - Change Page

01 | 02
---|---
Sequence ID | Direction

Direction values:
- `00h` - Up
- `01h` - Down
- `FFh` - Select current page

The receiving device will respond with message `F7h` describing the selected page.

### `F7h` - Current Page / Configure Page

01 | 02 | 03 | 04 | 05 - 08 | 09 - 0A
---|----|----|----|---------|---------
Sequence ID | Page | Channel | Node | Label | Units

Page values are 1 to 14. Channel is the ID of the value which will be
displayed. Node is the ID of the node that the device will use to source the
displayed value. This way, if there are multiple devices sending the same
data (e.g. two compasses), only values from the selected device will be
displayed. Label is an 8-character string displayed above the value,
uppercase ASCII only. Units is a 2-character string displayed above the
value, uppercase ASCII only.

> **Note:** To get a degree symbol in the units, send `%`.

### `F8h` - Store Page

01 |
---|
Sequence ID |

Just one byte, a sequence ID.

## 05. Formatting

The FFD and 20/20 displays are very flexible regarding data displayed.
Display mode is configured with a one or two byte bitmask. Not all possible
configurations make sense.

### First byte

Most significant bits (7,6):
- `00` - divide by 1
- `01` - divide by 2
- `10` - divide by 3
- `11` - divide by 4

Next bits (5,4):
- `00` - pad to 4 characters
- `01` - pad to 3 characters
- `10` - pad to 2 characters
- `11` - pad to 1 characters

Least significant bits (3,0):
- `0000` - No function
- `0001` - Signed 16-bit integer, -999 to 9999
- `0010` - Unsigned integer, single LCD segment, positionable
- `0011` - Unsigned integer, any character, leading or trailing
- `0100` - Time, 0 to 9999, no colon, 4 bytes
- `0101` - Time, 0 to 99, colon, 0 to 99, 4 bytes
- `0110` - Text
- `0111` - Unsinged Integer, 0 to 999, any character, trailing
- `1000` - Unsigned Integer, 0 to 511, any character, trailing
- `1001` - No function
- `1010` - No function
- `1011` - No function
- `1100` - No function
- `1101` - No function
- `1111` - No function

When using a divisor, it is advisable to ensure padding to make sure that
there is no space between the decimal and the value to the right of the
decimal. For example, if the value to display is `0001h` and the formatting
is configured as `B1h`, then the value will be displayed as `⎵⎵.⎵1`. Note
the odd spacing. You probably wanted `⎵0.01` (`91h`) or `00.01` (`81h`).
Recommended formatters are marked with †;

Format | Type                  | Range        | Width | Divisor | Data Format
-------|-----------------------|--------------|-------|---------|-------------
`01h`† | Signed 16-bit integer | -999 to 9999 |   4   |     1   | 2 bytes
`11h`† | Signed 16-bit integer | -999 to 9999 |   3   |     1   | 2 bytes
`21h`† | Signed 16-bit integer | -999 to 9999 |   2   |     1   | 2 bytes
`31h`† | Signed 16-bit integer | -999 to 9999 |   1   |     1   | 2 bytes
`41h`† | Signed 16-bit integer | -999 to 9999 |   4   |    10   | 2 bytes
`51h`† | Signed 16-bit integer | -999 to 9999 |   3   |    10   | 2 bytes
`61h`† | Signed 16-bit integer | -999 to 9999 |   2   |    10   | 2 bytes
`71h`  | Signed 16-bit integer | -999 to 9999 |   1   |    10   | 2 bytes
`81h`† | Signed 16-bit integer | -999 to 9999 |   4   |   100   | 2 bytes
`91h`† | Signed 16-bit integer | -999 to 9999 |   3   |   100   | 2 bytes
`A1h`  | Signed 16-bit integer | -999 to 9999 |   2   |   100   | 2 bytes
`B1h`  | Signed 16-bit integer | -999 to 9999 |   1   |   100   | 2 bytes
`C1h`† | Signed 16-bit integer | -999 to 9999 |   4   |  1000   | 2 bytes
`D1h`  | Signed 16-bit integer | -999 to 9999 |   3   |  1000   | 2 bytes
`E1h`  | Signed 16-bit integer | -999 to 9999 |   2   |  1000   | 2 bytes
`F1h`  | Signed 16-bit integer | -999 to 9999 |   1   |  1000   | 2 bytes
`02h`  | Same as 12
`12h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 3 | 1 | 2 bytes
`22h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 2 | 1 | 2 bytes
`32h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 1 | 1 | 2 bytes
`42h`  | Same as 52
`52h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 3 | 10 | 2 bytes
`62h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 2 | 10 | 2 bytes
`72h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 1 | 10 | 2 bytes
`82h`  | Same as 92
`92h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 3 | 100 | 2 bytes
`A2h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 2 | 100 | 2 bytes
`B2h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 1 | 100 | 2 bytes
`C2h`  | Same as D2
`D2h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 3 | 1000 | 2 bytes
`E2h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 2 | 1000 | 2 bytes
`F2h`  | Unsigned integer and raw LCD | 0 to 999, single segment, leading | 1 | 1000 | 2 bytes
`03h`  | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 3 | 1 | 2 bytes
`13h`  | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 2 | 1 | 2 bytes
`23h`  | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 1 | 1 | 2 bytes
`33h`  | Not Valid
`43h`  | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 3 | 10 | 2 bytes
`53h`  | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 2 | 10 | 2 bytes
`63h`  | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 1 | 10 | 2 bytes
`73h`  | Not Valid
`83h`  | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 3 | 100 | 2 bytes
`93h`  | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 2 | 100 | 2 bytes
`A3h`  | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 1 | 100 | 2 bytes
`B3h`  | Not Valid
`C3h`‡ | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 3 | 1000 | 2 bytes
`D3h`‡ | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 2 | 1000 | 2 bytes
`E3h`‡ | Unsigned integer and raw LCD | 0 to 255, any character, no d.p., leading or trailing | 1 | 1000 | 2 bytes
`F3h`  | Not Valid
`04h`  | Time | 0 to 9999 | | | 4 bytes
`05h`  | Time | 0 to 99, 0 to 99 | | | 4 bytes
`x6h`  | Raw LCD segments | | |
`07h`  | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 3 | 1
`17h`  | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 2 | 1
`27h`  | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 1 | 1
`37h`  | Not Valid
`47h`  | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 3 | 10
`57h`  | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 3 | 10
`67h`  | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 1 | 10
`77h`  | Not Valid
`87h`  | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 3 | 100
`97h`  | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 3 | 100
`A7h`  | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 3 | 100
`B7h`  | Not Valid
`C7h`‡ | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 3 | 1000
`D7h`‡ | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 3 | 1000
`E7h`‡ | Unsigned integer and raw LCD | 0 to 999, any character, no d.p., leading or trailing | 3 | 1000
`F7h`  | Not Valid
`08h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 3 | 1
`18h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 2 | 1
`28h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 1 | 1
`38h`  | Not Valid
`48h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 3 | 10
`58h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 2 | 10
`68h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 1 | 10
`78h`  | Not Valid
`88h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 3 | 100
`98h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 2 | 100
`a8h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 1 | 100
`b8h`  | Not Valid
`c8h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 3 | 1000
`d8h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 2 | 1000
`e8h`  | Unsigned integer and raw LCD | 0 to 511, any character, no d.p., trailing | 1 | 1000
`f8h`  | Not Valid

> ‡ While these work, they're effectively the same as `0xh` - `2xh` because there are only 3 digits available.

If you send the format byte by itself, the display shows an example. Sending it again formats the last received value

![7-segment](7segment.png)

### `1h`: Signed 16-bit int
16-bit integer values, no special formatting.

### `2h`: Unsigned 11-bit int, Movable LCD segment
High byte of 16-bit integer is masked as follows:

MSB|||||||LSB
-|-|-|-|-|-|-|-
7|6|5|4|3|2|1|0
z|z|z|y|y|x|x|x

`zzz` - Segment selection
- `000` - Decimal point
- `001` - c
- `010` - b
- `011` - a
- `100` - d
- `101` - e
- `110` - f
- `111` - g

`yy` - Position selection
- `00` - Character 4 (not super useful, occludes value)
- `01` - Character 3 (use with values in range 0-9, single digit width)
- `10` - Character 2 (use with values in range 0-99, two digit width)
- `11` - Character 1 (use with values in range 0-999, three digit width)

`xxx` - High bits of the displayed value.

### `3h`: Unsigned 8-bit int, Movable LCD character

First byte is the LCD character. It uses this addressing format. If the most
significant bit is set, then the character is displayed to the left of the
value. Otherwise, it is displayed to the right of the value. The second byte
is the value to be displayed.

MSB|||||||LSB
-|-|-|-|-|-|-|-
7|6|5|4|3|2|1|0
L/R|f|g|e|d|a|b|c

### `4h`: Undeciphered, invalid values can crash display

Format `47h` is `nn.nc` where n is a normal numeric value and c is a
directly addressable character. The high byte of the first 16-bit value is
ignored. The low byte of the first value is a character from the
_Positionable Letters_ table. `OR`ing with `80h` positions the letter to the
left. The second 16-bit number is displayed.



### `5h`: Time
Format `5h` is for displaying time. It is 4 bytes on the wire. It has two
formatting bytes, which are best left set to 0. Byte three is the value to
the left of the colon (hours or minutes). Byte four is the value to the
right of the colon (minutes or seconds).

This is not completely deciphered and invalid values can lead to the display
crashing, requiring a power cycle.

- `8000h` corrupt units
- `0800h` will cause an overflow, requiring a reset.
- `0500h` ibid.
- `0400h` ibid.
- `0300h` replace display with 0000, often crashes display
- `fc00h` display "RE" in units.
- `0200h` display "FR" in units.
- `0100h` clears units.



### `6h`: Text

Format `6h` is four bytes wide, one for each character. Digit one has a
decimal point on its right. Digit two decimal point bit controls the colon.
Digits 3 and 4 have the decimal point on their left. The high nybble of the
formatting byte has no effect, i.e. `06h`, `16h`, `26h`, etc. are all the
same.

MSB|||||||LSB
-|-|-|-|-|-|-|-
7|6|5|4|3|2|1|0
f|g|e|d|a|b|c|dp/colon

### `7h`: Unsigned Integer, 0 - 999 and Raw LCD

Format `7h` is followed by four bytes. The first byte is ignored. The
second is the bitmask for a raw character. If the most significant bit is 1,
it is displayed to the left of the value. If it is 0, the character is
displayed to the right.

### `8h`: Unsigned Integer, 0 - 511, and Raw LCD

Format `8h` is followed by two bytes. The high 7 bits of the 16-bit value
control the character. If no character is drawn (i.e. the high bits are 0),
then the value is right aligned.

## LCD Characters
These are 7-bit values. By default, if they share the screen with a numeric
value, they appear in the leftmost position. OR-ing with `80h` will move
them to the right of the numeric value. For formats where 8-bit character
values are used (e.g. `6h`), left shift these values one bit. The least
significant bit then controls the decimal point or colon.

The left-most character on the display has a decimal point on the right. The
second character has a colon instead of a decimal point. The right two
characters have a decimal point on the left.

Hex|Letter
---|------
5F | 0
03 | 1
3E | 2
2F | 3
63 | 4
6D | 5
7D | 6
07 | 7
7F | 8
6F | 9
77 | A
79 | b
5C | C
38 | c
3B | d
7C | E
74 | F
73 | H
1B | J
58 | L
39 | o
76 | P
67 | q
30 | r
78 | t
5B | U
19 | u
66 | degree
6E | underlined degree
20 | -
40 | '
42 | "

# 06. Configuring 20/20 Displays

The system needs to know what displays are available to be configured.
Therefore it should listen for "Hello" messages `0Ah` send by displays and
keep an internal list.

The first step is to send command `F6h` "Change page" with operator `FFh`,
which puts the display into programming mode. The display should being
flashing. It will also respond with `F7h` "Current page" which will provide
the stored configuration of the currently displayed page. This information
includes the channel, source node, and the 10-byte label.

The next step is to choose the page that needs to be configured. This is
done by sending the `F6h` "Change page" command with operator `00h` or `01h`
to move forward or backward in the list of pages until the desired page is
selected. On each page change, the device will again respond with `F7h`
"Current page".

When done, send the `F8h` "Select page" command. The device will respond
with `FDh`, which is simply an ACK.

To store a new page, send the `F7h` "Current page" command with the desired
configuration of page, channel, node, and label.

# 07. Resetting Devices

The reset command is `FEh`. Any recipent of this command will be reset to
factory defaults. For example, sending to `FFh` will reset all connected
devices, sending to `FAh` will reset just the 20/20 displays, and sending to
`40h` will reset just the 20/20 display at that address.

It has no payload.

# 08. Sending Latitude and Longitude

The lat/lon channel is `47h` and is sent with the command `03h`. It has a 16
byte payload that is interpreted as an ASCII string. The first byte doesn't
seem to do anything. The next six bytes are latitude in the format `DDMM.MM`.
Where `DD` is 0 to 90 degrees and `MM.MM` is fractional minutes. The next
byte is a cardinal direction, either `N` or `S`. The next seven bytes are
longitude in the format `DDDMM.MM`. Where `DDD` is 0 to 180 degrees and
`MM.MM` is fractional minutes. The last byte is a cardinal direction, either
`E` or `W`.

I have not been able to determine how to get the FFD to display anything
other than degrees, so it's not very useful. Position accuracy of 60nm is
... not great.

```
CmChSqLaLaD0D1D2D3CdLoLoLoD0D1D2D3Cd
0347003132000000004e3132330000000045 12N 123E
0347003132313435344e3132333231343745 12 14.54N 123 21.47E
0347803132313435344e3132333231343745 12 14.54N 123 21.47E
```

# 09. Configuring Data Senders

The factory defaults for FFD and 20/20 displays are listed below.

## Hydra Display

Page     | Channel | Source | Label
---------|---------|--------|-------
1 Top    |  `41h`  |  `01h` | BOAT SPD KT
1 Bottom |  `C1h`  |  `01h` | DEPTH    M
2 Top    |  `41h`  |  `01h` | BOAT SPD KT
2 Bottom |  `CFh`  |  `01h` | TRIP LOG NM
3 Top    |  `41h`  |  `01h` | BOAT SPD KT
3 Bottom |  `CDh`  |  `01h` | STD LOG  NM
4 Top    |  `41h`  |  `01h` | BOAT SPD KT
4 Bottom |  `1Eh`  |  `01h` | SEA TEMP °F

## Hydra 330 Display

Page     | Channel | Source | Label
---------|---------|--------|-------
1 Top    |  `41h`  |  `01h` | BOAT SPD KT
1 Bottom |  `75h`  |  `05h` | TIMER    MS
2 Top    |  `41h`  |  `01h` | AVG SPD  KT
2 Bottom |  `CFh`  |  `01h` | TRIP LOG NM
3 Top    |  `81h`  |  `01h` | D/R DIST NM
3 Bottom |  `D3h`  |  `01h` | D/R CRSE °M
4 Top    |  `CDh`  |  `01h` | STD LOG  NM
4 Bottom |  `1Eh`  |  `01h` | SEA TEMP °F

## 20/20 Display

Page | Channel | Source | Label
-----|---------|--------|-------------
   1 |  `41h`  |  `01h` | BOAT SPD KT
   2 |  `C1h`  |  `01h` | DEPTH    M
   3 |  `C2h`  |  `01h` | DEPTH    FT
   4 |  `4Dh`  |  `05h` | APP W/S  KT
   5 |  `51h`  |  `05h` | APP W/A  °
   6 |  `55h`  |  `05h` | TRUE W/S KT
   7 |  `59h`  |  `05h` | TRUE W/A °
   8 |  `6dh`  |  `05h` | TRUE DIR °
   9 |  `7Fh`  |  `05h` |   VMG    KT
  10 |  `49h`  |  `05h` | HEADING  °M
  11 |  `75h`  |  `05h` | TIMER    MS
  12 |  `E4h`  |  `09h` | BTW RMB  °M
  13 |  `EAh`  |  `09h` | CRSE O/G °M
  14 |  `EBh`  |  `09h` | SPD O/G  KT

For reasons unknown, some channels are selectable even if no CPU has
declared themselves as a source. Other channels are not until something
claims them. The following is a menu structure extracted from an FFD ROM
image. Different versions of the ROM have a different menu.

Each line starts with 3 bytes. The first is an index. The second is unknown,
but is likely a function pointer. The third (at least in the case of entries
related to channels) is the channel ID. Menu entries 02 - 0C, 12, and 13
have another byte after the label. This is the address of the default
sender. The menu items marked with an asterisk are available on the Hydra
330 FFD without a processor connected. The menu items with a second asterisk
are available on the Hydra FFD without a processor connected.

```
- 01 F1 01 CONTROL
  - 01 91 14 FREEZE
  - 02 83 15 RESET
  - 03 91 16 RUN
  - 04 91 17 START  0
  - 05 91 18 START  5
  - 06 91 19 START 10
  - 07 91 1A START 15
  - 08 91 1B RUN
  - 09 91 1C FREEZE
  - 0A 87 30 PERIOD
  - 0B 83 2F RESET
  - 0C 87 31 LEG BEAR
  - 0D 87 32 TIDE ON
  - 0E 87 1D SET
  - 0F 91 1E START
  - 10 91 1F STOP
  - 11 91 20 SYNC
- 02 01 02 SPEED
  - 01 00 41 BOAT SPDKT 01 * *
  - 02 00 64 AVG SPD KT 01 *
  - 03 00 7F   VMG   KT 05 *
- 03 01 03 LOG
  - 01 00 CD STD LOG NM 01 *
  - 02 00 CF TRIP LOGNM 01 *
- 04 01 04 DEPTH
  - 01 00 C1 DEPTH   M  01 * *
  - 02 00 C2 DEPTH   FT 01
  - 03 00 C3 DEPTH   FM 01
- 05 01 05 NAVIGATE
  - 01 00 49 HEADING %M 05 *
  - 02 00 29 OFF CRSE%  30
  - 03 00 D3 D/R CRSE%M 01 *
  - 04 00 81 D/R DISTNM 01 *
  - 05 00 69 COURSE  %M 05
  - 06 00 82 LEEWAY  %  05
  - 07 00 84 TIDE SET%M 09
  - 08 00 83 TIDE RTEKT 09
- 06 01 06 WIND
  - 01 00 4D APP W/S KT 05 *
  - 02 00 55 TRUE W/SKT 05 *
  - 03 00 51 APP W/A %  05 *
  - 04 00 59 TRUE W/A%  05 *
  - 05 00 6D TRUE DIR%M 05 *
  - 06 00 27 LIFT/HDR%  30
  - 07 00 6F N/L AWA %  09
  - 08 00 71 N/L AWS KT 09
  - 09 00 85 UPWASH     05
  - 0A 00 4F APP W/S MS 05
  - 0B 00 56 TRUE W/SMS 05
- 07 01 07 PERFORM
  - 01 00 32 TACKING    09
  - 02 00 33 REACHINGPC 09
  - 03 00 35 OPT W/A %  09
  - 04 00 E2 LAYLINE NM 09
  - 05 00 34 HEEL %     05
  - 06 00 7D TARG SPDKT 09
  - 07 00 9A OPP TACK%M 05
  - 08 00 9B  TRIM   %  05
  - 09 00 9C MAST ANG%  05
  - 0A 00 9D W/A MAST%  05
- 08 01 08 WAYPOINT
  - 01 00 E0 BRG W-W %T 09
  - 02 00 E1 BRG W-W %M 09
  - 03 00 E3 BTW RMB %T 09
  - 04 00 E4 BTW RMB %M 09
  - 05 00 E5 BTW GC  %T 09
  - 06 00 E6 BTW GC  %M 09 *
  - 07 00 E7 DTW RMB NM 09
  - 08 00 E8 DTW GC  NM 09 *
  - 09 00 E9 CRSE O/G%T 09
  - 0A 00 EA CRSE O/G%M 09 *
  - 0B 00 EB SPD O/G KT 09 *
  - 0C 00 EC VMG WPT KT 09
  - 0D 00 ED TTG WPT MS 09
  - 0E 00 EE CROSS TRNM 09
  - 0F 00 BB LATITUDE
  - 10 00 BC LONGTUDE
- 09 01 09 MOTOR
  - 01 00 8D VOLTS    V 05
- 0A 01 0A TEMP
  - 01 00 1F SEA TEMP%C 01
  - 02 00 1E SEA TEMP%F 01 * *
  - 03 00 1D AIR TEMP%C 05
  - 04 00 1C AIR TEMP%F 05
- 0B 01 0B TIME
  - 01 00 75 TIMER   MS 05 *
- 0C 01 0C MISC
  - 01 00 0B RUDDER  %  05
  - 02 00 38 LINEAR 1   05
  - 03 00 39 LINEAR 2   05
  - 04 00 3A LINEAR 3   05
  - 05 00 3B LINEAR 4   05
  - 06 00 87 BAROMETRMB 05
  - 07 00 86 PR TRENDMB 05
  - 08 A3 3A SOURCE  NR
- 0D 41 0D LIGHTING
  - 01 97 5B LOCAL         * *
  - 02 97 5C SYSTEM        * *
  - 03 97 5D RED           *
  - 04 97 5E GREEN         *
- 0E F9 0E ALARMS
  - 01 DB 22 ALL OFF
  - 02 93 23 SECTOR
  - 03 93 24 SECT ON
  - 04 93 25 SECT OFF
  - 05 93 26 HI ALARM
  - 06 93 27 HI ON
  - 07 93 28 HI OFF
  - 08 93 29 LO ALARM
  - 09 93 2A LO ON
  - 0A 93 2B LO OFF
- 0F FF 0F CNFG DSP
  - 01 81 3D PAGE          * *
  - 02 A1 3C NAV MODEGC
  - 03 A1 3B NAV MODERH
  - 04 93 38 SHOW ALM
  - 05 B5 3E REMOTE        * *
- 10 C5 10 DAMPING
  - 01 85 9A DAMPING SE
  - 02 87 51 DYN DAMP
- 11 F7 11 CALBRATE
  - 01 8D 53 AUTO CAL
  - 02 8B 54 MANL CAL
  - 03 8F 55 REF  CAL
  - 04 A7 5F USE SOG
  - 05 A9 60 CORRECTN
  - 06 89 56 CAL DISTNM
  - 07 89 57 STRT RUN
  - 08 89 58 STOP RUN
  - 09 89 59 END CAL
  - 0A 89 5A NEW CAL HZ
  - 0B 87 40 SINGLE  HZ
  - 0C 87 41 PORT CALHZ
  - 0D 87 42 STBD CALHZ
  - 0E B3 61 TACK CRN
  - 0F 87 62 BSPD TBL
  - 10 87 66 FILTER  PC
  - 11 87 63 SET TACK
  - 12 87 64 SET HEEL%
  - 13 87 65 OFFSET  PC
  - 14 87 43 OFFSET  KT
  - 15 87 44 DATUM
  - 16 87 45 MHU ANGL%
  - 17 87 52 HEEL CRN
  - 18 87 46 MHU CAL HZ
  - 19 87 47 MHU OFFSKT
  - 1A 87 48 CAL VAL1
  - 1B 87 49 CAL VAL2
  - 1C 87 4A CAL VAL3
  - 1D 87 4B CAL VAL4
  - 1E 87 4F CORRECTN
- 12 01 12 PARAMTR
  - 01 00 36 GAIN    DB 01
  - 02 00 37 NOISE   DB 01
- 13 01 13 EXTERNAL
  - 01 00 EF REMOTE 0   09
  - 02 00 F0 REMOTE 1   09
  - 03 00 F1 REMOTE 2   09
  - 04 00 F2 REMOTE 3   09
  - 05 00 F3 REMOTE 4   09
  - 06 00 F4 REMOTE 5   09
  - 07 00 F5 REMOTE 6   09
  - 08 00 F6 REMOTE 7   09
  - 09 00 F7 REMOTE 8   09
  - 0A 00 F8 REMOTE 9   09
```

In order for more of these menu items to be available, a processor must claim them as data it will provide. The `FCh` command will do this.

`FC` `ssccxxyyccxxyyccxxyy`

SS is a sequence ID.

CC is a channel ID.

XXYY is unknown at this point, but 0000 seems to work fine.

You can send as many CCXXYY groups in a single message as you want. Or at
least up to 84, since any more than that would make the packet too long.

### MISC

- FFD menu CAL VAL1 sends command `CFh` with `0138h`.
- FFD menu CAL VAL2 sends command `D0h` with `0238h`.
- FFD menu CAL VAL3 sends command `D1h` with `0338h`.
- FFD menu DAMPING sends command `CDh` with `0538h`.
