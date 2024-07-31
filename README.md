# ILI948x_t4x_p
## A basic display driver for ILI948X series on a Teensy 4.1 and Micromod and limited T4

**Disclaimer: This is an experimental library, currently a WIP. I cannot guarantee that all functions will work nor can I guarantee that this library will work with other libraries. Use at your own risk**  

This library can communicate with an ILI9488/9486/9481 TFT LCD via an 8 bit parallel interface (8080)
It utilizes FlexIO and DMA to write data to the screen while offloading the task from the CPU.

There is now added support for 16 bit parallel as well.  But this is even more WIP.

First include the library and create a constructor:
```
#include "ILI948x_t4x_p.h"
#define CS 5
#define DC 4
#define RST 3
ILI948x_t4x_p lcd = ILI948x_t4x_p(DC,CS,RST);
```
You can use and GPIO pins for CS, DC and RST

Next, wire up your LCD - use Teensy pins:

Default Micromod FlexIO Pins:  The Data pins must be consecutive Flexio pins
Note: The are FLEXIO 2 pins on the Micromod The flexio pins shown in ()
* pin 10 - WR (0)
* pin 12 - RD (1)
* pin 40 - D0 (4)
* pin 41 - D1 (5)
* pin 42 - D2 (6)
* pin 43 - D3 (7)
* pin 44 - D4 (8)
* pin 45 - D5 (9)
* pin 6 - D6 (10)
* pin 9 - D7 (11)

Default Teensy 4.1 FlexIO pins:
These are on FlexIO 3 which does not support DMA
* pin 36 - WR (18)
* pin 37 - RD (19)
* pin 19 - D0 (0)
* pin 18 - D1
* pin 14 - D2
* pin 15 - D3
* pin 40 - D4
* pin 41 - D5
* pin 17 - D6
* pin 16 - D7 (7)

When in 16 bit mode add these:
* pin 22 - D8 (8)
* pin 23 - D9
* pin 20 - D10
* pin 21 - D11
* pin 38 - D12
* pin 39 - D13
* pin 26 - D14
* pin 27 - D15 (15)

Teensy 4 support - The Teensy 4 does not have 8 onsecutive flexIO pins: So it is special cased:
There are 2 groups of 4, so the code has to convert each byte going out to 10 bits and
convert from 10 bits back to 8 on input:

* pin 20 - RD (10)
* pin 21 - WR (11)
* pin 19 - D0 (0)
* pin 18 - D1 (1)
* pin 14 - D2 (2)
* pin 15 - D3 (3)
* pin 17 - D4 (6)
* pin 16 - D5 (7)
* pin 22 - D6 (8)
* pin 23 - D7 (9)

For those Teensy boards that cans support 16 data pins, you can setup to use that mode using:
	tft.setBusWidth(16);

Likewise if there are different sets of pins that could be used, you can use the method setFlxIOPins
There are two versions of this API:

A short hand version, where you set the write pin, read pin and first data pin and it computes the rest 
```
    bool setFlexIOPins(uint8_t write_pin, uint8_t rd_pin, uint8_t tft_d0 = 0xff);
```
Or one that you explicitly set all of them.  
```
    // Set the FlexIO pins.  Specify all of the pins for 8 bit mode. Must be called before begin
    bool setFlexIOPins(uint8_t write_pin, uint8_t rd_pin, 
                       uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                       uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7,
                       uint8_t d8=0xff, uint8_t d9=0xff, uint8_t d10=0xff, uint8_t d11=0xff,
                       uint8_t d12=0xff, uint8_t d13=0xff, uint8_t d14=0xff, uint8_t d15=0xff);
```
Note: the D8-D15 are only needed if you have setup for 16 bit modes.

These flexIO configuration setting methods need to be called prior to calling the begin method.
   
in the setup function call:
```
ILI948x_t4x_p::begin();
```
The default baud rate is 20Mhz

In the begin(n) function you can pass 2,4,8,12,20,24, 30 and 40 to lower or raise the baud rate.

This version now has support for most of the graphic functions in several of our SPI libraries
such as ILI9341_t3n and ILI9488_t3.  

Call the following function for a polling method write:
```
ILI948x_t4x_p::pushPixels16bit(flexio_teensy_mm,0,0,480,320);
```
or call the following function for an async DMA write
```
ILI948x_t4x_p::pushPixels16bitDMA(flexio_teensy_mm,0,0,480,320);
```
to push the image data, the arguments are as follows:
* uint16_t color array (RGB565)
* uint16_t x1
* uint16_t y1
* uint16_t x2
* uint16_t y2

Additional API's:


Set rotation: 1,2,3,4
```
ILI948x_t4x_p::setRotation(n);
```

Invert display color (true/false)
```
ILI948x_t4x_p::invertDisplay(bool);
```

Register a callback to trigger when the DMA transfer completes - ONLY ON DMA METHOD
```
ILI948x_t4x_p::onCompleteCB(CBF callback);
```
![Image of TFT with Teensy MM image](https://github.com/david-res/ILI948x_t4x_p/blob/master/mm_flexio_example.jpg)

