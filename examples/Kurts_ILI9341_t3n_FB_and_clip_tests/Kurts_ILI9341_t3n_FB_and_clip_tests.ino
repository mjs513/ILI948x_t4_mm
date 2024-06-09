#include <Teensy_Parallel_GFX.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include "ILI948x_t4_mm.h"
#include "font_Arial.h"
#include "font_ArialBold.h"
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>

#define ROTATION 3

#define KURTS_MICROMOD

#include "SPI.h"

//Adafruit_GFX_Button button;

// Let's allocate the frame buffer ourself.
//DMAMEM uint16_t tft_frame_buffer[ILI9488_TFTWIDTH * ILI9488_TFTHEIGHT];

uint8_t use_dma = 0;
uint8_t use_clip_rect = 0;
uint8_t use_set_origin = 0;
uint8_t use_fb = 0;

#define ORIGIN_TEST_X 50
#define ORIGIN_TEST_Y 50

ILI948x_t4_mm tft = ILI948x_t4_mm(13,11,12, 7); //(dc, cs, rst, rd)

void setup() {
  while (!Serial && (millis() < 4000)) ;
  Serial.begin(115200);

  if (CrashReport) {
    Serial.print(CrashReport);
    WaitForUserInput();
  }
  //Serial.printf("Begin: CS:%d, DC:%d, MOSI:%d, MISO: %d, SCK: %d, RST: %d\n", TFT_CS, TFT_DC, TFT_MOSI, TFT_MISO, TFT_SCK, TFT_RST);
  #ifdef TFT_TOUCH_CS
  pinMode(TFT_TOUCH_CS, OUTPUT);
  digitalWrite(TFT_TOUCH_CS, HIGH);
  #endif

  tft.begin();
  
//  tft.setFrameBuffer(tft_frame_buffer);

  tft.setRotation(ROTATION);
  tft.fillScreen(ILI9488_BLACK);

//  
//  button.initButton(&tft, 200, 125, 100, 40, ILI9488_GREEN, ILI9488_YELLOW, ILI9488_RED, "UP", 1, 1);

  drawTestScreen();
}

void SetupOrClearClipRectAndOffsets() {
  if (use_clip_rect) {
    tft.setClipRect();  // make sure we clear the whole screen
    tft.setOrigin();    // make sure none are set yet

    tft.fillScreen(ILI9488_LIGHTGREY);

    // Now lets set origin.
    if (use_set_origin)
      tft.setOrigin(ORIGIN_TEST_X, ORIGIN_TEST_Y);
    int x = tft.width() / 4;
    int y = tft.height() / 4;
    int w = tft.width() / 2;
    int h = tft.height() / 2;
    tft.drawRect(x, y, w, h, ILI9488_ORANGE);
  //  tft.updateScreen();
    tft.setClipRect(x + 1, y + 1, w - 2, h - 2);
    delay(250);

  } else {
    tft.setClipRect();
    if (use_set_origin)
      tft.setOrigin(ORIGIN_TEST_X, ORIGIN_TEST_Y);
    else
      tft.setOrigin();
  }
}


uint16_t palette[256];  // Should probably be 256, but I don't use many colors...
uint16_t pixel_data[2500];
const uint8_t pict1bpp[] = {0xff, 0xff, 0xc0, 0x03, 0xa0, 0x05, 0x90, 0x9, 0x88, 0x11, 0x84, 0x21, 0x82, 0x41, 0x81, 0x81,
                            0x81, 0x81, 0x82, 0x41, 0x84, 0x21, 0x88, 0x11, 0x90, 0x09, 0xa0, 0x05, 0xc0, 0x03, 0xff, 0xff
                           };
const uint8_t pict2bpp[] = {
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff, 0x00, 0x00, 
  0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff, 0x00, 0x00, 
  0xaa, 0xaa, 0xff, 0xff, 0x00, 0x00, 0x55, 0x55, 
  0xaa, 0xaa, 0xff, 0xff, 0x00, 0x00, 0x55, 0x55, 
  0xff, 0xff, 0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 
  0xff, 0xff, 0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff,
  0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff, 0x00, 0x00, 
  0x55, 0x55, 0xaa, 0xaa, 0xff, 0xff, 0x00, 0x00, 
  0xaa, 0xaa, 0xff, 0xff, 0x00, 0x00, 0x55, 0x55, 
  0xaa, 0xaa, 0xff, 0xff, 0x00, 0x00, 0x55, 0x55, 
  0xff, 0xff, 0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 
  0xff, 0xff, 0x00, 0x00, 0x55, 0x55, 0xaa, 0xaa, 
};
const uint8_t pict4bpp[] = {  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00,  
  0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00,  
  0x00, 0x11, 0x22, 0x22, 0x22, 0x22, 0x11, 0x00,
  0x00, 0x11, 0x22, 0x22, 0x22, 0x22, 0x11, 0x00,
  0x00, 0x11, 0x22, 0x33, 0x33, 0x22, 0x11, 0x00,
  0x00, 0x11, 0x22, 0x33, 0x33, 0x22, 0x11, 0x00,
  0x00, 0x11, 0x22, 0x33, 0x33, 0x22, 0x11, 0x00,
  0x00, 0x11, 0x22, 0x33, 0x33, 0x22, 0x11, 0x00,
  0x00, 0x11, 0x22, 0x22, 0x22, 0x22, 0x11, 0x00,
  0x00, 0x11, 0x22, 0x22, 0x22, 0x22, 0x11, 0x00,
  0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00,  
  0x00, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00,  
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


                           
void drawTestScreen() {
  Serial.printf("Use FB: %d ", use_fb); Serial.flush();
//  tft.useFrameBuffer(use_fb);
  SetupOrClearClipRectAndOffsets();
  uint32_t start_time = millis();
  tft.fillScreen(use_fb ? ILI9488_RED : ILI9488_BLACK);
  //tft.setFont(Inconsolata_60);
  tft.setFont(Arial_24_Bold);
  tft.setTextColor(ILI9488_WHITE);
  tft.setCursor(0, 0);
  tft.println("Test");
  tft.setTextColor(ILI9488_WHITE, ILI9488_RED);
  tft.println("text");
  tft.setCursor(85, 65);
  tft.print("XYZ");
  tft.setFontAdafruit();
  tft.setTextSize(2);
  tft.setTextColor(ILI9488_WHITE);
  tft.println("01234");
  tft.setTextColor(ILI9488_WHITE, ILI9488_GREEN);
  tft.println("56789!@#$%");

  tft.drawRect(0, 150, 100, 50, ILI9488_WHITE);
  tft.drawLine(0, 150, 100, 50, ILI9488_GREEN);
  tft.fillRectVGradient(125, 150, 50, 50, ILI9488_GREEN, ILI9488_YELLOW);
  tft.fillRectHGradient(200, 150, 50, 50, ILI9488_YELLOW, ILI9488_GREEN);
  // Try a read rect and write rect

#if 0
  tft.readRect(0, 0, 50, 50, pixel_data);
  // For heck of it lets make sure readPixel and ReadRect 
  // give us same data, maybe check along diagnal?
  for (uint i=0; i < 50; i++) {
    uint16_t pixel_color = tft.readPixel(i,i);
    if (pixel_color != pixel_data[i*50+i]) {
      Serial.printf("Read rect/pixel mismatch: %d %x %x\n", i, pixel_color,pixel_data[i*50+i]);
    }    
  }

#ifdef DEBUG_PIN
  digitalWrite(DEBUG_PIN, LOW);
#endif
  tft.writeRect(250, 0, 50, 50, pixel_data);

  // Lets try to pack this rectangle of data into 8 byte
  tft.readRect(85, 65, 50, 50, pixel_data);
  uint16_t *ppd16 = pixel_data;
  uint8_t *ppd8 = (uint8_t*)pixel_data;
  uint8_t palette_cnt = 0;
  int palette_index;
  for (int i = 0; i < 2500; i++) {
    for (palette_index = 0; palette_index < palette_cnt; palette_index++) {
      if (*ppd16 == palette[palette_index])
        break;
    }
    if (palette_index >= palette_cnt) {
      palette[palette_cnt++] = *ppd16;  // save away the color
    }
    *ppd8++ = palette_index;
    ppd16++;
  }
  tft.writeRect8BPP(200, 50, 50, 50, (uint8_t*)pixel_data, palette);
  #endif

  palette[0] = ILI9488_CYAN; 
  palette[1] = ILI9488_OLIVE; 
  tft.writeRect1BPP(75, 100, 16, 16, pict1bpp, palette);
  tft.writeRect1BPP(320 - 90, 75, 16, 16, pict1bpp, palette);
  
  palette[2] = ILI9488_MAROON; 
  palette[3] = ILI9488_PINK; 
  tft.writeRect2BPP(75, 125, 32, 16, pict2bpp, palette);

  tft.writeRectNBPP(15, 125, 32, 16, 2, pict2bpp, palette);
  tft.writeRectNBPP(75, 150, 16, 16, 4, pict4bpp, palette);

  // Try drawing button
  tft.setFontAdafruit();
  //button.drawButton();

  Serial.println(millis() - start_time, DEC);

  
  use_fb = use_fb ? 0 : 1 ;
  Serial.println(use_fb, DEC);


}

void fillScreenTest() {
  //tft.useFrameBuffer(0);
  SetupOrClearClipRectAndOffsets();

  tft.fillScreen(ILI9488_RED);
  WaitForUserInput();
  tft.fillScreen(ILI9488_GREEN);
  WaitForUserInput();
  tft.fillScreen(ILI9488_WHITE);
  WaitForUserInput();
  tft.fillScreen(ILI9488_BLACK);

}
void printTextSizes(const char *sz) {
#if 0    
  Serial.printf("%s(%d,%d): SPL:%u ", sz, tft.getCursorX(), tft.getCursorY(), tft.strPixelLen(sz));
  int16_t x, y;
  uint16_t w, h;
  tft.getTextBounds(sz, tft.getCursorX(), tft.getCursorY(), &x, &y, &w, &h);
  Serial.printf(" Rect(%d, %d, %u %u)\n", x, y, w, h);  
  tft.drawRect(x, y, w, h, ILI9488_GREEN);
#endif  
}


void drawTextScreen(bool fOpaque) {
  SetupOrClearClipRectAndOffsets();
  tft.setTextSize(1);
  uint32_t start_time = millis();
//  tft.useFrameBuffer(use_fb);
  tft.fillScreen(use_fb ? ILI9488_RED : ILI9488_BLACK);
  tft.setFont(Arial_28_Bold);
//t  tft.setFont(Arial_40_Bold);
  if (fOpaque)
    tft.setTextColor(ILI9488_WHITE, use_fb ? ILI9488_BLACK : ILI9488_RED);
  else
    tft.setTextColor(ILI9488_WHITE);
  tft.setCursor(0, 5);
  tft.println("AbCdEfGhIj");
#if 0
  tft.setFont(Arial_28_Bold);
  tft.println("0123456789!@#$");
  tft.setFont(Arial_20_Bold);
  tft.println("abcdefghijklmnopq");
  tft.setFont(Arial_14_Bold);
  tft.println("ABCDEFGHIJKLMNOPQRST");
  tft.setFont(Arial_10_Bold);
  tft.println("0123456789zyxwvutu");
#endif
  tft.setFont(&FreeMonoBoldOblique12pt7b);
  printTextSizes("AdaFruit_MB_12");
  if (fOpaque){
    tft.setTextColor(ILI9488_RED, ILI9488_BLUE);
    tft.print("A");
    tft.setTextColor(ILI9488_WHITE, ILI9488_GREEN);
    tft.print("d");
    tft.setTextColor(ILI9488_RED, ILI9488_BLUE);
    tft.print("a");
    tft.setTextColor(ILI9488_WHITE, ILI9488_GREEN);
    tft.print("F");
    tft.setTextColor(ILI9488_RED, ILI9488_BLUE);
    tft.print("R");
    tft.setTextColor(ILI9488_WHITE, ILI9488_GREEN);
    tft.print("u");
    tft.setTextColor(ILI9488_RED, ILI9488_BLUE);
    tft.print("i");
    tft.setTextColor(ILI9488_WHITE, ILI9488_GREEN);
    tft.print("t");
    tft.setTextColor(ILI9488_RED, ILI9488_BLUE);
    tft.print("_");
    tft.setTextColor(ILI9488_WHITE, ILI9488_GREEN);
    tft.print("M");
    tft.setTextColor(ILI9488_RED, ILI9488_BLUE);
    tft.print("B");
    tft.setTextColor(ILI9488_WHITE, ILI9488_GREEN);
    tft.print("_");
    tft.setTextColor(ILI9488_RED, ILI9488_BLUE);
    tft.print("1");
    tft.setTextColor(ILI9488_WHITE, ILI9488_GREEN);
    tft.println("2");
    tft.setTextColor(ILI9488_WHITE, use_fb ? ILI9488_BLACK : ILI9488_RED);
  }
  else tft.println("AdaFruit_MB_12");
  tft.setFont(&FreeSerif12pt7b);
  printTextSizes("FreeSan12");
  tft.println("FreeSan12");
  tft.println();
  tft.setTextSize(1,3);
  printTextSizes("Size 1,3");
  tft.println("Size 1,3");
  tft.setFont();
  tft.setCursor(0, 190);
  tft.setTextSize(1,2);
  printTextSizes("Sys(1,2)");
  tft.println("Sys(1,2)");
  tft.setTextSize(1);
  printTextSizes("System");
  tft.println("System");
  tft.setTextSize(1);


  //tft.updateScreen();
  Serial.printf("Use FB: %d OP: %d, DT: %d OR: %d\n", use_fb, fOpaque, use_set_origin, millis() - start_time);
}


void drawGFXTextScreen(bool fOpaque) {
  SetupOrClearClipRectAndOffsets();
  tft.setTextSize(1);
  tft.setCursor(0, 10);
  if (fOpaque)
    tft.setTextColor(ILI9488_WHITE, use_fb ? ILI9488_BLACK : ILI9488_RED);
  else
    tft.setTextColor(ILI9488_WHITE);
  uint32_t start_time = millis();
  //tft.useFrameBuffer(use_fb);
  tft.fillScreen(use_fb ? ILI9488_RED : ILI9488_BLACK);
  tft.setFont(&FreeMonoBoldOblique12pt7b);
  tft.println("MonoBold");
  tft.println("ABCDEFGHIJKLMNO");
  tft.println("abcdefghijklmno");
  tft.println("0123456789!@#$%^&*()_");
  tft.setFont(&FreeSerif12pt7b);
  tft.println("Serif12");
  tft.println("ABCDEFGHIJKLMNO");
  tft.println("abcdefghijklmno");
  tft.println("0123456789!@#$%^&*()_");
  //tft.updateScreen();
  tft.setTextSize(1);
  tft.setFont();
  Serial.printf("Use FB: %d OP: %d, DT: %d\n", use_fb, fOpaque, millis() - start_time);
}
//=============================================================================
// Wait for user input
//=============================================================================
void WaitForUserInput() {
  Serial.println("Hit Enter to continue");
  Serial.flush();
  while (Serial.read() == -1) ;
  while (Serial.read() != -1) ;

}


void loop(void) {
  // See if any text entered
  int ich;
  if ((ich = Serial.read()) != -1) {
    while (Serial.read() != -1) delay(1);

    // See if We have a dma operation in progress?

    if (ich == 'c') {
      use_clip_rect = !use_clip_rect;
      if (use_clip_rect) Serial.println("Clip Rectangle Turned on");
      else Serial.println("Clip Rectangle turned off");
      return;
    }
    if (ich == 'd') {
      use_dma = !use_dma;
      if (use_dma) Serial.println("DMA Turned on");
      else Serial.println("DMA turned off");
      return;
    }

    if (ich == 's') {
      use_set_origin = !use_set_origin;
      if (use_set_origin) Serial.printf("Set origin to %d, %d\n", ORIGIN_TEST_X, ORIGIN_TEST_Y);
      else Serial.println("Clear origin");
      return;
    }
    if (ich == 'o')
      drawTextScreen(1);
    else if (ich == 'f')
      fillScreenTest();
    else if (ich == 't')
      drawTextScreen(0);
    else if (ich == 'g')
      drawGFXTextScreen(0);
    else
      drawTestScreen();
  }

}
