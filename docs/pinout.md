
## Wemos D1 Mini Pro pinout

I am using information about pins/GPIO from the following article: https://escapequotes.net/wemos-d1-mini-pro/

| Pin	| Function	                   |  ESP-8266 Pin
|-------|------------------------------|---------------  |
| TX	| TXD	                       |  TXD  |
| RX	| RXD	                       |  RXD  |
| A0	| Analog input, max 3.2V	   |  A0  |
| D0	| IO	                       |  GPIO16  |
| D1	| IO, SCL	                   |  GPIO5  |
| D2	| IO, SDA	                   |  GPIO4  |
| D3	| IO, 10k Pull-up	           |  GPIO0  |
| D4	| IO, 10k Pull-up, BUILTIN_LED |  GPIO2  |
| D5	| IO, SCK	                   |  GPIO14  |
| D6	| IO, MISO	                   |  GPIO12  |
| D7	| IO, MOSI	                   |  GPIO13  |
| D8	| IO, 10k Pull-down, SS	       |  GPIO15  |
| G	    | Ground	                   |  GND  |
| 5V	| 5V	                       |  -  |
| 3V3	| 3.3V	                       |  3.3V  |
| RST	| Reset	                       |  RST  |

### Experminents
Initial tests failed.
I was not able to set up 4 output digital pins for the setup.

I wrote a simple routinge for RemoteDebug that made it possible to change the mode of different GPIOs and then displayed modes of different pins.
This way I wanted to check empirically how what pins can be used as output.

Here are some intermediary results of some experminets.

I was able to put the following pins into OUTPUT mode (as validated by getPinModes function, not validated "phisically"):
* gpio1 (?)
* gpio2 (d4)
* gpio3 (?)
* gpio4 (d2)
* gpio5 (d1)
* gpio16 (is it builtin led?)

I was not able to set OUTPUT mode for the following pins:
* gpio12-15


Now I'll try to check the actual pins with multimeter.


set5 and 4 (d1, d2) works

set2 (d4) disables the led, unset2 enables the led (builtin) -- acutally it confirms the information from "Wemos D1 Mini Pro pinout" section;
            on the other hand, it steers the builtin led, why doesn't it control d4 pin? -- something with function1/2

set3 works

GPIO01, GPIO03 work as output, but then I am not able to do any remote debugging. No serial communication works. Moreover, RemoteDebug doesn't work either. (although it is supposed to be network-based...)


XXX TODO:
read: https://github.com/xreef/PCF8574_library/issues/14