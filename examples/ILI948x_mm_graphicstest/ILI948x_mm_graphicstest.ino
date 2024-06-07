
#include <Adafruit_GFX.h>
#include <Teensy_Parallel_GFX.h>

#include "ILI948x_t4_mm.h"
#include "flexio_teensy_mm.c"
ILI948x_t4_mm lcd = ILI948x_t4_mm(13,11,12); //(dc, cs, rst)

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print(CrashReport);
  
  lcd.begin(30);
  lcd.setBitDepth(16);
  test_display();
  lcd.setRotation(3);

  delay(1000);
  
  Serial.println(F("Benchmark                Time (microseconds)"));

  Serial.print(F("Screen fill              "));
  Serial.println(testFillScreen());
  delay(200);

  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(600);

  Serial.print(F("Lines                    "));
  Serial.println(testLines(ILI9488_CYAN));
  delay(500);

  Serial.print(F("Horiz/Vert Lines         "));
  Serial.println(testFastLines(ILI9488_RED, ILI9488_BLUE));
  delay(500);

  Serial.print(F("Circles (filled)         "));
  Serial.println(testFilledCircles(10, ILI9488_MAGENTA));

  Serial.print(F("Circles (outline)        "));
  Serial.println(testCircles(10, ILI9488_WHITE));
  delay(200);

  Serial.print(F("Rectangles (outline)     "));
  Serial.println(testRects(ILI9488_GREEN));
  delay(500);

  Serial.print(F("Rectangles (filled)      "));
  Serial.println(testFilledRects(ILI9488_YELLOW, ILI9488_MAGENTA));
  delay(500);

  Serial.print(F("Triangles (outline)      "));
  Serial.println(testTriangles());
  delay(200);

  Serial.print(F("Triangles (filled)       "));
  Serial.println(testFilledTriangles());
  delay(1200);

  Serial.print(F("Rounded rects (outline)  "));
  Serial.println(testRoundRects());
  delay(200);

  Serial.print(F("Rounded rects (filled)   "));
  Serial.println(testFilledRoundRects());
  delay(200);

  Serial.println(F("Done!"));
}

void loop() {
  for(uint8_t rotation=0; rotation<4; rotation++) {
    lcd.setRotation(rotation);
    testText();
    delay(1000);
  }

  delay(1000);
  lcd.pushPixels16bit(flexio_teensy_mm,0,0,479,319); // 480x320
  delay(1000);
  lcd.pushPixels16bitDMA(flexio_teensy_mm,0,0,479,319); // 480x320
  delay(1000);
}


unsigned long testText() {
  lcd.fillScreen(ILI9488_BLACK);
  unsigned long start = micros();
  lcd.setCursor(0, 0);
  lcd.setTextColor(ILI9488_WHITE);  lcd.setTextSize(1);
  lcd.println("Hello World!");
  lcd.setTextColor(ILI9488_YELLOW); lcd.setTextSize(2);
  lcd.println(1234.56);
  lcd.setTextColor(ILI9488_RED);    lcd.setTextSize(3);
  lcd.println(0xDEADBEEF, HEX);
  lcd.println();
  lcd.setTextColor(ILI9488_GREEN);
  lcd.setTextSize(5);
  lcd.println("Groop");
  lcd.setTextSize(2);
  lcd.println("I implore thee,");
  lcd.setTextSize(1);
  lcd.println("my foonting turlingdromes.");
  lcd.println("And hooptiously drangle me");
  lcd.println("with crinkly bindlewurdles,");
  lcd.println("Or I will rend thee");
  lcd.println("in the gobberwarts");
  lcd.println("with my blurglecruncheon,");
  lcd.println("see if I don't!");
  return micros() - start;
}

void test_display() {
  lcd.setRotation(3);
  lcd.fillScreen(ILI9488_RED);
  delay(500);
  lcd.fillScreen(ILI9488_GREEN);
  delay(500);
  lcd.fillScreen(ILI9488_BLUE);
  delay(500);
  lcd.fillScreen(ILI9488_BLACK);
  delay(500);
  lcd.setRotation(0);
}


unsigned long testFillScreen() {
  unsigned long start = micros();
  lcd.fillScreen(ILI9488_BLACK);
  lcd.fillScreen(ILI9488_RED);
  lcd.fillScreen(ILI9488_GREEN);
  lcd.fillScreen(ILI9488_BLUE);
  lcd.fillScreen(ILI9488_BLACK);
  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = lcd.width(),
                h = lcd.height();

  lcd.fillScreen(ILI9488_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) lcd.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) lcd.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  lcd.fillScreen(ILI9488_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for(x2=0; x2<w; x2+=6) lcd.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) lcd.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  lcd.fillScreen(ILI9488_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) lcd.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for(y2=0; y2<h; y2+=6) lcd.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  lcd.fillScreen(ILI9488_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for(x2=0; x2<w; x2+=6) lcd.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for(y2=0; y2<h; y2+=6) lcd.drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = lcd.width(), h = lcd.height();

  lcd.fillScreen(ILI9488_BLACK);
  start = micros();
  for(y=0; y<h; y+=5) lcd.drawFastHLine(0, y, w, color1);
  for(x=0; x<w; x+=5) lcd.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}


unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = lcd.width(), h = lcd.height(), r2 = radius * 2;

  lcd.fillScreen(ILI9488_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      lcd.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = lcd.width()  + radius,
                h = lcd.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      lcd.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}


unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = lcd.width()  / 2,
                cy = lcd.height() / 2;

  lcd.fillScreen(ILI9488_BLACK);
  n     = min(lcd.width(), lcd.height());
  start = micros();
  for(i=2; i<n; i+=6) {
    i2 = i / 2;
    lcd.drawRect(cx-i2, cy-i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = lcd.width()  / 2 - 1,
                cy = lcd.height() / 2 - 1;

  lcd.fillScreen(ILI9488_BLACK);
  n = min(lcd.width(), lcd.height()) - 1;
  for(i=n; i>0; i-=6) {
    i2    = i / 2;
    start = micros();
    lcd.fillRect(cx-i2, cy-i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    lcd.drawRect(cx-i2, cy-i2, i, i, color2);
  }

  return t;
}


unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = lcd.width()  / 2 - 1,
                      cy = lcd.height() / 2 - 1;

  lcd.fillScreen(ILI9488_BLACK);
  n     = min(cx, cy);
  start = micros();
  for(i=0; i<n; i+=5) {
    lcd.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      lcd.color565(0, 0, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = lcd.width()  / 2 - 1,
                   cy = lcd.height() / 2 - 1;

  lcd.fillScreen(ILI9488_BLACK);
  start = micros();
  for(i=min(cx,cy); i>10; i-=5) {
    start = micros();
    lcd.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      lcd.color565(0, i, i));
    t += micros() - start;
    lcd.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
      lcd.color565(i, i, 0));
  }

  return t;
}


unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = lcd.width()  / 2 - 1,
                cy = lcd.height() / 2 - 1;

  lcd.fillScreen(ILI9488_BLACK);
  w     = min(lcd.width(), lcd.height()) - 1;
  start = micros();
  for(i=0; i<w; i+=6) {
    i2 = i / 2;
    lcd.drawRoundRect(cx-i2, cy-i2, i, i, i/8, lcd.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = lcd.width()  / 2 - 1,
                cy = lcd.height() / 2 - 1;

  lcd.fillScreen(ILI9488_BLACK);
  start = micros();
  for(i=min(lcd.width(), lcd.height()) - 1; i>20; i-=6) {
    i2 = i / 2;
    lcd.fillRoundRect(cx-i2, cy-i2, i, i, i/8, lcd.color565(0, i, 0));
  }

  return micros() - start;
}