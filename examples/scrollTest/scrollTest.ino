/***************************************************
  This is our GFX example for the Adafruit ILI9488 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include <Teensy_Parallel_GFX.h>
#include <Adafruit_GFX.h>  // Core graphics library
#include "ILI948x_t4x_p.h"
#include <ILI9488_t3_font_ComicSansMS.h>

//#define TEENSY64

ILI948x_t4x_p tft = ILI948x_t4x_p(13, 11, 7);  //(dc, cs, rst, rd)

void setup() {

  Serial.begin(9600);
 
  tft.begin(ILI9488, 20);
  tft.setBitDepth(16);

  tft.setRotation(3);

  tft.fillScreen(ILI9488_BLACK);
  while (!Serial) ; 
  tft.setTextColor(ILI9488_WHITE);  tft.setTextSize(4);
  tft.enableScroll();
  tft.setScrollTextArea(0,0,120,240);
  tft.setScrollBackgroundColor(ILI9488_GREEN);

  tft.setCursor(180, 100);

  tft.setFont(ComicSansMS_12);
  tft.print("Fixed text");

  tft.setCursor(0, 0);

  tft.setTextColor(ILI9488_BLACK); 

  for(int i=0;i<20;i++){
    tft.print("  this is line ");
    tft.println(i);
    delay(500);
  }

  tft.fillScreen(ILI9488_BLACK);
  tft.setScrollTextArea(40,50,120,120);
  tft.setScrollBackgroundColor(ILI9488_GREEN);
  tft.setFont(ComicSansMS_10);

  tft.setTextSize(1);
  tft.setCursor(40, 50);

  for(int i=0;i<20;i++){
    tft.print("  this is line ");
    tft.println(i);
    delay(500);
  }


}



void loop(void) {


}
