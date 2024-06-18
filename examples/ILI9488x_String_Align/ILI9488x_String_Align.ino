/*
Tests string alignment

Normally strings are printed relative to the top left corner but this can be
changed with the setTextDatum() function. The library has #defines for:

TL_DATUM = Top left
TC_DATUM = Top centre
TR_DATUM = Top right
ML_DATUM = Middle left
MC_DATUM = Middle centre
MR_DATUM = Middle right
BL_DATUM = Bottom left
BC_DATUM = Bottom centre
BR_DATUM = Bottom right
*/

// Set which Display we are using and at what speed
// Currently I have options for both MICROMOD and T42 to make it
// easier for testing
#ifdef ARDUINO_TEENSY_MICROMOD
#define ILI948X ILI9486
#define ILI948X_SPEED_MHX 24
#elif defined(ARDUINO_TEENSY41)
#define ILI948X ILI9488
#define ILI948X_SPEED_MHX 24
#endif


#include <Teensy_Parallel_GFX.h>
#include "ILI948x_t4x_p.h"
#include <SPI.h>
#include <ili9488_t3_font_Arial.h>

#ifdef ARDUINO_TEENSY41
ILI948x_t4x_p tft = ILI948x_t4x_p(10, 8, 9);  //(dc, cs, rst)
#else
ILI948x_t4x_p tft = ILI948x_t4x_p(4, 5, 3);  //(dc, cs, rst)
#endif

unsigned long drawTime = 0;

void setup(void) {
    Serial.begin(115200);

    // Begin optionally change FlexIO pins.
    //    WRITE, READ, D0, [D1 - D7]
    //    tft.setFlexIOPins(7, 8);
    //    tft.setFlexIOPins(7, 8, 40);
    //    tft.setFlexIOPins(7, 8, 40, 41, 42, 43, 44, 45, 6, 9);
    //tft.setFlexIOPins(7, 8);
    tft.begin(ILI948X, ILI948X_SPEED_MHX);
    tft.setBitDepth(16);
    tft.setRotation(3);
    tft.setFont(Arial_18);
    //tft.setTextSize(4);
}

void loop() {

    tft.fillScreen(ILI9488_BLACK);

    for (byte datum = 0; datum < 9; datum++) {
        tft.setTextColor(ILI9488_WHITE, ILI9488_BLACK);

        tft.setTextDatum(datum);

        tft.drawNumber(88, 160, 60);
        tft.fillCircle(160, 120, 5, ILI9488_RED);

        tft.setTextDatum(datum);

        tft.setTextColor(ILI9488_YELLOW);
        tft.drawString("TEENSY 4", 5, 160, 120);
        delay(1000);
        tft.fillScreen(ILI9488_BLACK);
    }

    tft.setTextDatum(MC_DATUM);

    tft.setTextColor(ILI9488_BLACK);
    tft.drawString("X", 160, 120);
    delay(1000);
    tft.fillScreen(ILI9488_BLACK);

    tft.setTextDatum(MC_DATUM);

    tft.setTextColor(ILI9488_BLACK);
    tft.drawString("X", 160, 120);
    delay(1000);
    tft.fillScreen(ILI9488_BLACK);

    tft.setTextColor(ILI9488_WHITE, ILI9488_BLUE);

    tft.setTextDatum(MC_DATUM);

    //Test floating point drawing function
    float test = 67.125;
    tft.drawFloat(test, 4, 160, 180);
    delay(1000);
    tft.fillScreen(ILI9488_BLACK);
    test = -0.555555;
    tft.drawFloat(test, 3, 160, 180);
    delay(1000);
    tft.fillScreen(ILI9488_BLACK);
    test = 0.1;
    tft.drawFloat(test, 4, 160, 180);
    delay(1000);
    tft.fillScreen(ILI9488_BLACK);
    test = 9999999;
    tft.drawFloat(test, 1, 160, 180);
    delay(1000);

    tft.fillCircle(160, 180, 5, ILI9488_YELLOW);

    tft.setTextDatum(MC_DATUM);

    tft.setTextColor(ILI9488_BLACK);
    tft.drawString("X", 160, 180);

    delay(4000);
}
