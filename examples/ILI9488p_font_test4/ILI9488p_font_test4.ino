//-------------------------------------------------------------------
//
// This test program illustrates a one method of using ILI9341 fonts
// and Adafruit fonts with ILI9488 display.
//
// this sketch is in the public domain.
//
// This sketch depends on the fonts that are contained in the library
//     https://github.com/mjs513/ILI9341_fonts
//-------------------------------------------------------------------

// Set which Display we are using and at what speed
// Currently I have options for both MICROMOD and T42 to make it
// easier for testing
#ifdef ARDUINO_TEENSY_MICROMOD
#define ILI948X ILI9486
#define ILI948X_SPEED_MHX 24
#elif defined(ARDUINO_TEENSY41) || defined(ARDUINO_TEENSY40)
#define ILI948X ILI9488
#define ILI948X_SPEED_MHX 24
#endif


#include <Adafruit_GFX.h>
#include <Teensy_Parallel_GFX.h>

#include <SPI.h>
#include "ILI948x_t4x_p.h"

#include "font_Arial.h"
#include "font_ArialBold.h"
#include "font_ComicSansMS.h"
#include "font_OpenSans.h"
#include "font_DroidSans.h"
#include "font_Michroma.h"
#include "font_Crystal.h"
#include "font_ChanceryItalic.h"

#define CENTER ILI948x_t4x_p::CENTER

// maybe a few GFX FOnts?
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>

typedef struct {
    const ILI948x_t4_mm_font_t *ili_font;
    const GFXfont *gfx_font;
    const char *font_name;
    uint16_t font_fg_color;
    uint16_t font_bg_color;
} ili_fonts_test_t;


const ili_fonts_test_t font_test_list[] = {
    { nullptr, nullptr, "SystemFont", ILI9488_WHITE, ILI9488_WHITE },
    { nullptr, nullptr, "SystemFont", ILI9488_RED, ILI9488_YELLOW },
    { &Arial_12, nullptr, "Arial_12", ILI9488_WHITE, ILI9488_WHITE },
    { &Arial_12_Bold, nullptr, "ArialBold 12", ILI9488_YELLOW, ILI9488_YELLOW },
    { &ComicSansMS_12, nullptr, "ComicSansMS 12", ILI9488_GREEN, ILI9488_GREEN },
    { &DroidSans_12, nullptr, "DroidSans_12", ILI9488_WHITE, ILI9488_WHITE },
    { &Michroma_12, nullptr, "Michroma_12", ILI9488_YELLOW, ILI9488_YELLOW },
    { &Crystal_16_Italic, nullptr, "CRYSTAL_16", ILI9488_BLACK, ILI9488_YELLOW },
    { &Chancery_16_Italic, nullptr, "Chancery_16_Italic", ILI9488_GREEN, ILI9488_GREEN },
    { &OpenSans16, nullptr, "OpenSans 16", ILI9488_RED, ILI9488_YELLOW },
    { nullptr, &FreeMono9pt7b, "GFX FreeMono9pt7b", ILI9488_WHITE, ILI9488_WHITE },
    { nullptr, &FreeMono9pt7b, "GFX FreeMono9pt7b", ILI9488_RED, ILI9488_YELLOW },
    { nullptr, &FreeSerif9pt7b, "GFX FreeSerif9pt7b", ILI9488_WHITE, ILI9488_WHITE },
    { nullptr, &FreeSerif9pt7b, "GFX FreeSerif9pt7b", ILI9488_RED, ILI9488_YELLOW },

};

#ifdef ARDUINO_TEENSY41
ILI948x_t4x_p tft = ILI948x_t4x_p(10, 8, 9);  //(dc, cs, rst)
#elif ARDUINO_TEENSY40
ILI948x_t4x_p tft = ILI948x_t4x_p(0, 1, 2);  //(dc, cs, rst)
#else
ILI948x_t4x_p tft = ILI948x_t4x_p(4, 5, 3);  //(dc, cs, rst)
#endif

uint8_t test_screen_rotation = 0;


void setup() {
    Serial.begin(38400);
    long unsigned debug_start = millis();
    while (!Serial && ((millis() - debug_start) <= 5000))
        ;
    Serial.println("Setup");

    // Begin optionally change FlexIO pins.
    //    WRITE, READ, D0, [D1 - D7]
    //    tft.setFlexIOPins(7, 8);
    //    tft.setFlexIOPins(7, 8, 40);
    //    tft.setFlexIOPins(7, 8, 40, 41, 42, 43, 44, 45, 6, 9);
    //tft.setFlexIOPins(7, 8);
    tft.begin(ILI948X, ILI948X_SPEED_MHX);

    tft.setBitDepth(16);
    tft.setRotation(4);
    tft.fillScreen(ILI9488_BLACK);

    tft.setTextColor(ILI9488_WHITE);
    tft.setFont(Arial_12);
    tft.println("Arial_12");
    displayStuff();

    tft.setTextColor(ILI9488_YELLOW);
    tft.setFont(Arial_12_Bold);
    tft.println("ArialBold 12");
    displayStuff();
    nextPage();
    tft.setTextColor(ILI9488_GREEN);
    tft.setFont(ComicSansMS_12);
    tft.println("ComicSansMS 12");
    displayStuff();


    tft.setTextColor(ILI9488_WHITE);
    tft.setFont(DroidSans_12);
    tft.println("DroidSans_12");
    displayStuff();
    nextPage();

    tft.setTextColor(ILI9488_YELLOW);
    tft.setFont(Michroma_12);
    tft.println("Michroma_12");
    displayStuff();

    tft.setTextColor(ILI9488_BLACK, ILI9488_YELLOW);
    tft.setFont(Crystal_16_Italic);
    tft.println("CRYSTAL_16");
    displayStuff();

    nextPage();

    tft.setTextColor(ILI9488_GREEN);
    tft.setFont(Chancery_16_Italic);
    tft.println("Chancery_16_Italic");
    displayStuff();

    //anti-alias font OpenSans
    tft.setTextColor(ILI9488_RED, ILI9488_YELLOW);
    tft.setFont(OpenSans16);
    tft.println("OpenSans 18");
    displayStuff();

    Serial.println("Basic Font Display Complete");
    Serial.println("Loop test for alt colors + font");
}

void loop() {
    tft.setFont(Arial_12);
    Serial.printf("\nRotation: %d\n", test_screen_rotation);
    tft.setRotation(test_screen_rotation);
    tft.fillScreen(ILI9488_RED);
    tft.setCursor(CENTER, CENTER);
    tft.printf("Rotation: %d", test_screen_rotation);
    test_screen_rotation = (test_screen_rotation + 1) & 0x3;
    /*  tft.setCursor(200, 300);
    Serial.printf("  Set cursor(200, 300), retrieved(%d %d)",
                  tft.getCursorX(), tft.getCursorY());
  */
    tft.setCursor(25, 25);
    tft.write('0');
    tft.setCursor(tft.width() - 25, 25);
    tft.write('1');
    tft.setCursor(25, tft.height() - 25);
    tft.write('2');
    tft.setCursor(tft.width() - 25, tft.height() - 25);
    tft.write('3');

    for (uint8_t font_index = 0; font_index < (sizeof(font_test_list) / sizeof(font_test_list[0])); font_index++) {
        nextPage();
        if (font_test_list[font_index].font_fg_color != font_test_list[font_index].font_bg_color)
            tft.setTextColor(font_test_list[font_index].font_fg_color, font_test_list[font_index].font_bg_color);
        else
            tft.setTextColor(font_test_list[font_index].font_fg_color);
        if (font_test_list[font_index].ili_font) tft.setFont(*font_test_list[font_index].ili_font);
        else if (font_test_list[font_index].gfx_font) tft.setFont(font_test_list[font_index].gfx_font);
        else tft.setFont();
        tft.println(font_test_list[font_index].font_name);
        displayStuff1();
    }
    nextPage();
}

uint32_t displayStuff() {
    elapsedMillis elapsed_time = 0;
    tft.println("ABCDEFGHIJKLM");
    tft.println("nopqrstuvwxyz");
    tft.println("0123456789");
    tft.println("!@#$%^ &*()-");
    tft.println();
    tft.println();
    return (uint32_t)elapsed_time;
}

uint32_t displayStuff1() {
    elapsedMillis elapsed_time = 0;
    tft.println("ABCDEFGHIJKLM");
    tft.println("nopqrstuvwxyz");
    tft.println("0123456789");
    tft.println("!@#$%^ &*()-");

    int16_t cursorX = tft.getCursorX();
    int16_t cursorY = tft.getCursorY();

    uint16_t width = tft.width();
    uint16_t height = tft.height();
    Serial.printf("DS1 (%d,%d) %d %d\n", cursorX, cursorY, width, height);
    uint16_t rect_x = width / 2 - 50;
    uint16_t rect_y = height - 50;
    tft.drawRect(rect_x, rect_y, 100, 40, ILI9488_WHITE);
    for (uint16_t y = rect_y + 5; y < rect_y + 40; y += 5)
        tft.drawFastHLine(rect_x + 1, y, 98, ILI9488_PINK);
    for (uint16_t x = rect_x + 5; x < rect_x + 100; x += 5)
        tft.drawFastVLine(x, rect_y + 1, 38, ILI9488_PINK);
    tft.setCursor(width / 2, height - 30, true);
    tft.print("Center");

    // Lets try again with CENTER X keyword.
    rect_y -= 60;
    tft.drawRect(rect_x, rect_y, 100, 40, ILI9488_PINK);
    for (uint16_t y = rect_y + 5; y < rect_y + 40; y += 5)
        tft.drawFastHLine(rect_x + 1, y, 98, ILI9488_CYAN);
    for (uint16_t x = rect_x + 5; x < rect_x + 100; x += 5)
        tft.drawFastVLine(x, rect_y + 1, 38, ILI9488_CYAN);
    tft.setCursor(CENTER, rect_y);
    tft.print("XCENTR");

    // Lets try again with CENTER Y keyword.
    rect_x = 50;
    rect_y = tft.height() / 2 - 25;
    tft.drawRect(rect_x, rect_y, 100, 50, ILI9488_CYAN);
    for (uint16_t y = rect_y + 5; y < rect_y + 50; y += 5)
        tft.drawFastHLine(rect_x + 1, y, 98, ILI9488_PINK);
    for (uint16_t x = rect_x + 5; x < rect_x + 100; x += 5)
        tft.setCursor(50, CENTER);
    tft.print("YCENTR");



    tft.setCursor(cursorX, cursorY);
    static const char alternating_text[] = "AbCdEfGhIjKlM\rNoPqRsTuVwXyZ";

    for (uint8_t i = 0; i < (sizeof(alternating_text) - 1); i++) {
        if (i & 1) tft.setTextColor(ILI9488_WHITE, ILI9488_RED);
        else tft.setTextColor(ILI9488_YELLOW, ILI9488_BLUE);
        tft.write(alternating_text[i]);
    }

    tft.println();
    tft.println();



    return (uint32_t)elapsed_time;
}

void nextPage() {
    Serial.println("Press anykey to continue");
    while (Serial.read() == -1)
        ;
    while (Serial.read() != -1)
        ;

    tft.fillScreen(ILI9488_BLACK);
    tft.setCursor(0, 0);
}
