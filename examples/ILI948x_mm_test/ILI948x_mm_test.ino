#include "ILI948x_t4_mm.h"
#include "flexio_teensy_mm.c"
ILI948x_t4_mm lcd = ILI948x_t4_mm(13,11,7); //(dc, cs, rst)

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print(CrashReport);
  
  lcd.begin(ILI9488, 30);
  lcd.setBitDepth(16);
  lcd.displayInfo();
  lcd.setRotation(3);
}

void loop() {
  lcd.pushPixels16bit(flexio_teensy_mm,0,0,479,319); // 480x320
  delay(3000);
  lcd.fillScreen(ILI9488_BLACK);
  delay(1000);
  lcd.pushPixels16bitDMA(flexio_teensy_mm,0,0,479,319); // 480x320
  delay(3000);
  lcd.fillScreen(ILI9488_BLACK);
  delay(1000);
  lcd.writeRect(0, 0, 480, 320, flexio_teensy_mm); // 480x320
  delay(2000);

}
