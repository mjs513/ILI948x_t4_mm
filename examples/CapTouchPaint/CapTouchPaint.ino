/***************************************************
  This is a modified version of the painting example
  from Adafruit_FT6206, that is modified to work with
  the NT35510

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#define ILI9488X ILI9486
#define ILI9488X_SPEED_MHZ 24
#define BUS_WIDTH 8
#define BIT_DEPTH 16
#define CTP_INT_PIN 22 // 0xff if pin is not connected
#define ROTATION 3
//#define SHOW_TOUCH_INFO

#include <Wire.h>  // this is needed for FT6206
#include <FT6x36_t4.h>
#include <ILI948x_t4x_p.h>
#include <Teensy_Parallel_GFX.h>
#include <Adafruit_GFX.h>  // Core graphics library

// The FT6206 uses hardware I2C (SCL/SDA)
//Adafruit_FT6206 ctp = Adafruit_FT6206();
FT6x36_t4 ctp(CTP_INT_PIN);

#ifdef ARDUINO_TEENSY41
ILI948x_t4x_p tft = ILI948x_t4x_p(10, 8, 9);  //(dc, cs, rst)
#elif ARDUINO_TEENSY40
ILI948x_t4x_p tft = ILI948x_t4x_p(0, 1, 2);  //(dc, cs, rst)
#elif defined(ARDUINO_TEENSY_DEVBRD4)
ILI948x_t4x_p tft = ILI948x_t4x_p(10, 11, 12);  //(dc, cs, rst)
#elif defined(ARDUINO_TEENSY_DEVBRD5)
#undef ROTATION
#define ROTATION 3
#if BUS_WIDTH == 18
ILI948x_t4x_p tft = ILI948x_t4x_p(55, 59, 54);  //(dc, cs, rst)
#else
ILI948x_t4x_p tft = ILI948x_t4x_p(55, 53, 54);  //(dc, cs, rst)
#endif
#else
ILI948x_t4x_p tft = ILI948x_t4x_p(4, 5, 3);  //(dc, cs, rst)
#endif



// Size of the color selection boxes and the paintbrush size
#define BOXSIZE 60
#define PENRADIUS 3
int oldcolor, currentcolor;

void setup(void) {
    Serial.begin(115200);
    while (!Serial) delay(10);  // pause the serial port

    Serial.println(F("Cap Touch Paint!"));

#if defined(ARDUINO_TEENSY_DEVBRD4)
    Serial.print("DEVBRD4 - ");
#elif defined(ARDUINO_TEENSY_DEVBRD5)
    Serial.print("DEVBRD5 - ");
    tft.setBusWidth(BUS_WIDTH);
//    tft.setFlexIOPins(56, 52, 40);
#elif defined(ARDUINO_TEENSY_MICROMOD)
    Serial.print("Micromod - ");
#elif defined(ARDUINO_TEENSY41)
    Serial.print("Teensy4.1 - ");
#endif
    Serial.println(ILI9488X_SPEED_MHZ);
#ifdef ARDUINO_TEENSY41
    pinMode(24, INPUT_PULLDOWN);
    delay(10);  // plenty of time
    // if the user tied this pin to 3.3v then try 16 bit bus...
    Serial.printf("Pin 24, %u\n", digitalRead(24));
    tft.setBusWidth(digitalRead(24) ? 16 : 8);
#endif

    Serial.println("Before tft.begin");
    Serial.flush();
    tft.begin(ILI9488X, ILI9488X_SPEED_MHZ);
    tft.setRotation(ROTATION);

    Serial.printf("Before setBitDepth: %u\n", BIT_DEPTH);
    Serial.flush();
    tft.setBitDepth(BIT_DEPTH);

    Serial.println("Before displayInfo");
    Serial.flush();
    tft.displayInfo();
    tft.fillScreen(ILI9488_RED);

    Serial.println("\n*** Start Touch controller ***");
    Wire.begin();
//    if (!ctp.begin(&Wire, 0x38)) {  // Optional pass in which Wire object and device ID
    if (!ctp.begin()) {  // Use default: Wire and 0x38
        Serial.println("Couldn't start FT6236 touchscreen controller");
        while (1) delay(10);
    }

    Serial.println("Capacitive touchscreen started");
    ctp.showAllRegisters();
    tft.fillScreen(ILI9488_BLACK);

    // make the color selection boxes
    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9488_RED);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9488_YELLOW);
    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, ILI9488_GREEN);
    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, ILI9488_CYAN);
    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, ILI9488_BLUE);
    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, ILI9488_MAGENTA);

    // select the current color 'red'
    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9488_WHITE);
    currentcolor = ILI9488_RED;
}

// quick and dirty conversion struct;
typedef struct {
    uint16_t x;
    uint16_t y;
} point_t;

void loop() {
    // Wait for a touch
    if (!ctp.touched()) {
        return;
    }

    // Retrieve a point
    point_t p;
    //TS_Point p = ctp.getPoint();
    ctp.touchPoint(p.x, p.y);

    // Print out raw data from screen touch controller

    uint8_t gesture = ctp.gesture();
    if (gesture) {
      Serial.printf("!! Gesture: %u\n", gesture);
    }

    #ifdef SHOW_TOUCH_INFO
    Serial.print("X = ");
    Serial.print(p.x);
    Serial.print("\tY = ");
    Serial.print(p.y);
    Serial.print(" -> ");
    #endif

// flip it around to match the screen.
#if ROTATION == 3
    int y = map(p.x, 0, 320, 0, tft.height());
    p.x = map(p.y, 480, 0, 0, tft.width());
    p.y = y;
#else
    p.x = map(p.x, 0, 240, 240, 0);
    p.y = map(p.y, 0, 320, 320, 0);
#endif
    // Print out the remapped (rotated) coordinates
    #ifdef SHOW_TOUCH_INFO
    Serial.print("(");
    Serial.print(p.x);
    Serial.print(", ");
    Serial.print(p.y);
    Serial.println(")");
    #endif

    if (p.y < BOXSIZE) {
        oldcolor = currentcolor;

        if (p.x < BOXSIZE) {
            currentcolor = ILI9488_RED;
            tft.drawRect(0, 0, BOXSIZE, BOXSIZE, ILI9488_WHITE);
        } else if (p.x < BOXSIZE * 2) {
            currentcolor = ILI9488_YELLOW;
            tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9488_WHITE);
        } else if (p.x < BOXSIZE * 3) {
            currentcolor = ILI9488_GREEN;
            tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, ILI9488_WHITE);
        } else if (p.x < BOXSIZE * 4) {
            currentcolor = ILI9488_CYAN;
            tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, ILI9488_WHITE);
        } else if (p.x < BOXSIZE * 5) {
            currentcolor = ILI9488_BLUE;
            tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, ILI9488_WHITE);
        } else if (p.x <= BOXSIZE * 6) {
            currentcolor = ILI9488_MAGENTA;
            tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, ILI9488_WHITE);
        }

        if (oldcolor != currentcolor) {
            if (oldcolor == ILI9488_RED)
                tft.fillRect(0, 0, BOXSIZE, BOXSIZE, ILI9488_RED);
            if (oldcolor == ILI9488_YELLOW)
                tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, ILI9488_YELLOW);
            if (oldcolor == ILI9488_GREEN)
                tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, ILI9488_GREEN);
            if (oldcolor == ILI9488_CYAN)
                tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, ILI9488_CYAN);
            if (oldcolor == ILI9488_BLUE)
                tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, ILI9488_BLUE);
            if (oldcolor == ILI9488_MAGENTA)
                tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, ILI9488_MAGENTA);
        }
    }
    if (((p.y - PENRADIUS) > BOXSIZE) && ((p.y + PENRADIUS) < tft.height())) {
        tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
    }
    if (Serial.available()) {
      while(Serial.read() != -1) {}
      ctp.showAllRegisters();
    }
}