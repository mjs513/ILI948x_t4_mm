#ifndef _ILI948x_t4_mm_H_
#define _ILI948x_t4_mm_H_

// uncomment below the line corresponding to your screen:

// #define ILI9481_1
// #define ILI9481_2
// #define ILI9486
// #define ILI9488
// #define R61529

#include "Arduino.h"
#include "DMAChannel.h"
#include "FlexIO_t4.h"

#include "Teensy_Parallel_GFX.h"

#define SHIFTNUM 4            // number of shifters used (must be 1, 2, 4, or 8)
#define SHIFTER_DMA_REQUEST 3 // only 0, 1, 2, 3 expected to work

#define DATABUFBYTES (480 * 320) / 4

#define _TFTWIDTH 320  // ILI9488 TFT width in default rotation
#define _TFTHEIGHT 480 // ILI9488 TFT height in default rotation

#define ILI9488_NOP 0x00     // No-op
#define ILI9488_SWRESET 0x01 // Software reset
#define ILI9488_RDDID 0x04   // Read display ID
#define ILI9488_RDDST 0x09   // Read display status

#define ILI9488_SLPIN 0x10  // Enter Sleep Mode
#define ILI9488_SLPOUT 0x11 // Sleep Out
#define ILI9488_PTLON 0x12  // Partial Mode ON
#define ILI9488_NORON 0x13  // Normal Display Mode ON

#define ILI9488_RDMODE 0x0A     // Read Display Power Mode
#define ILI9488_RDMADCTL 0x0B   // Read Display MADCTL
#define ILI9488_RDCOLMOD 0x0C   // Read Display Pixel Format
#define ILI9488_RDIMGFMT 0x0D   // Read Display Image Mode
#define ILI9488_RDDSM 0x0E      // Read Display Signal Mode
#define ILI9488_RDSELFDIAG 0x0F // Read Display Self-Diagnostic Result

#define ILI9488_INVOFF 0x20   // Display Inversion OFF
#define ILI9488_INVON 0x21    // Display Inversion ON
#define ILI9488_GAMMASET 0x26 // Gamma Set
#define ILI9488_DISPOFF 0x28  // Display OFF
#define ILI9488_DISPON 0x29   // Display ON

#define ILI9488_CASET 0x2A // Column Address Set
#define ILI9488_PASET 0x2B // Page Address Set
#define ILI9488_RAMWR 0x2C // Memory Write
#define ILI9488_RAMRD 0x2E // Memory Read

#define ILI9488_PTLAR 0x30    // Partial Area
#define ILI9488_TEOFF 0x34    // Tearing effect line off
#define ILI9488_TEON 0x35     // Tearing effect line on
#define ILI9488_MADCTL 0x36   // Memory Access Control
#define ILI9488_VSCRSADD 0x37 // Vertical Scrolling Start Address
#define ILI9488_COLMOD 0x3A   // Interface pixel format

#define ILI9488_TESLWR 0x44 // Write tear scan line

#define ILI9488_FRMCTR1 0xB1 // Frame Rate Control (Normal Mode / Full Colors)
#define ILI9488_FRMCTR2 0xB2 // Frame Rate Control (Idle Mode / 8 Colors)
#define ILI9488_FRMCTR3 0xB3 // Frame Rate Control (Partial Mode / Full Colors)
#define ILI9488_INVCTR 0xB4  // Display Inversion Control
#define ILI9488_DFUNCTR 0xB6 // Display Function Control
#define ILI9488_ETMOD 0xB7   // Entry Mode Set

#define ILI9488_PWCTR1 0xC0    // Power Control 1
#define ILI9488_PWCTR2 0xC1    // Power Control 2
#define ILI9488_PWCTR3 0xC2    // Power Control 3 (For Normal Mode)
#define ILI9488_PWCTR4 0xC3    // Power Control 4 (For Idle Mode)
#define ILI9488_PWCTR5 0xC4    // Power Control 5 (For Partial Mode)
#define ILI9488_VMCTR1 0xC5    // VCOM Control
#define ILI9488_CABCCTRL1 0xC6 // CABC Control 1
#define ILI9488_CABCCTRL2 0xC8 // CABC Control 2

#define ILI9488_NVMEMWR 0xD0  // NV Memory Write 
#define ILI9488_NVMEMPROTKEY  0xD1  //NV Memory Protection Key
#define ILI9488_NVMEMSTATRD 0xD2  //NV Memory Status Read

#define ILI9488_PGAMCTRL 0xE0 // Positive Gamma Control
#define ILI9488_NGAMCTRL 0xE1 // Negative Gamma Control
#define ILI9488_SETIMAGE 0xE9 // Set Image Function

#define ILI9488_ADJCTL3 0xF7

#define ILI9488_RDID1 0xDA // Read ID1 value
#define ILI9488_RDID2 0xDB // Read ID2 value
#define ILI9488_RDID3 0xDC // Read ID3 value

#define MADCTL_MY 0x80  // Bottom to top
#define MADCTL_MX 0x40  // Right to left
#define MADCTL_MV 0x20  // Row/Column exchange
#define MADCTL_ML 0x10  // LCD refresh Bottom to top
#define MADCTL_RGB 0x00 // Red-Green-Blue pixel order
#define MADCTL_BGR 0x08 // Blue-Green-Red pixel order
#define MADCTL_MH 0x04  // LCD refresh right to left
#define MADCTL_GS 0x01
#define MADCTL_SS 0x02

// MADCTL 0,1,2,3 for setting rotation and 4 for screenshot
/*
#if defined (ILI9488) || defined (ILI9486)
#define MADCTL_ARRAY { MADCTL_MX | MADCTL_BGR, MADCTL_MV | MADCTL_BGR, MADCTL_MY | MADCTL_BGR, MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR, MADCTL_MY | MADCTL_MV | MADCTL_BGR } // ILI9488/9486
#elif defined (ILI9481_1) || defined (ILI9481_2)
#define MADCTL_ARRAY { MADCTL_BGR | MADCTL_SS, MADCTL_MV | MADCTL_BGR, MADCTL_BGR | MADCTL_GS, MADCTL_MV | MADCTL_BGR | MADCTL_SS | MADCTL_GS } // ILI9481
#elif defined (R61529)
#define MADCTL_ARRAY { MADCTL_RGB, MADCTL_MV | MADCTL_MX | MADCTL_RGB, MADCTL_RGB | MADCTL_GS | MADCTL_MX, MADCTL_MV | MADCTL_RGB | MADCTL_GS } // R61529
#endif
*/

/****************************************************************************************/
// #define ILI9488_CLOCK_READ 30   //equates to 8mhz
#define ILI9488_CLOCK_READ 60 // equates to 4mhz
// #define ILI9488_CLOCK_READ 120   //equates to 2mhz

enum {
    ILI9488 = 0,
    ILI9486 = 1,
    ILI9486_1 = 2,
    ILI9486_2 = 3,
    R61529 = 4
};

//--------------------------------------------------
static const uint8_t ILI9488_init_commands[] = {
  1, 120, 0x01, // SW RST
  1, 15, 0x11, // Exit sleep
  1, 15, 0x28, // Display Off
  3, 0, 0xC0, 0x19, 0x1A,
  3, 0, 0xC1,0x45,0x00,
  2, 0, 0xC2, 0x33,
  4, 0, 0xC5,0x00,0x12,0x80,
  2, 0, 0xB4, 0x02,
  4, 0, 0xB6,0x00,0x02,0x3B,
  2, 0, 0xB7,0x07,
  16, 0, 0xE0,0x00,0x03,0x09,0x08,0x16,0x0A,0x3F,0x78,0x4C,0x09,0x0A,0x08,0x16,0x1A,0x0F,
  16, 0, 0xE1,0x00,0x16,0x19,0x03,0x0F,0x05,0x32,0x45,0x46,0x04,0x0E,0x0D,0x35,0x37,0x0F,
  2, 10, 0x36, 0x48,
  1, 120, 0x29, // Display On
  0
};


static const uint8_t ILI9486_init_commands[] = {
  1, 120, 0x01,
  1, 20, 0x11, // Sleep out, also SW reset
  2, 0, 0x3A, 0x55,
  2, 0, 0xC2, 0x44,
  5, 0, 0xC5, 0x00, 0x00, 0x00, 0x00,
  16, 0, 0xE0, 0x0F,0x1F,0x1C,0x0C,0x0C,0x08,0x48,0x98,0x37,0x0A,0x13,0x04,0x11,0x0D,0x00,
  16, 0, 0xE1,0x0F,0x32,0x2E,0x0B,0x0D,0x05,0x47,0x75,0x37,0x06,0x10,0x03,0x24,0x20,0x00,
  2, 0, 0x36, 0x48,
  1, 0, 0x20,
  1, 120, 0x29, // Display ON
  0
};

static const uint8_t ILI9481_1_init_commands[] = {
  1, 120, ILI9488_SWRESET,
  1, 20, ILI9488_SLPOUT,
  4, 0, ILI9488_NVMEMWR, 0x07, 0x41, 0x1D,
  4, 0, ILI9488_NVMEMPROTKEY, 0x00, 0x2B, 0x1F,
  3, 0, ILI9488_NVMEMSTATRD, 0x01, 0x11 ,
  7, 0, ILI9488_PWCTR1,	0x10,	0x3B,	0x00,	0x02,	0x11,	0x00,
  2, 0, ILI9488_VMCTR1, 0x03,
  2, 0, ILI9488_CABCCTRL1, 0x80,
  13, 0, ILI9488_CABCCTRL2,	0x00,	0x14,	0x33,	0x10,	0x00,	0x16,	0x44,	0x36,	0x77,	0x00,	0x0F,	0x00,
  2, 0, 0xB0, 0x00,
  2, 0, 0xE4, 0xA0,
  2, 0, 0xF0, 0x08,
  3, 0, 0xF3, 0x40, 0x0A,
  1, 0, 0xF6, 0x84,
  1, 0, ILI9488_ADJCTL3, 0x80,
  5, 0, ILI9488_FRMCTR3,	0x00,	0x01,	0x06,	0x30,
  1, 0, ILI9488_INVCTR, 0x00,
  2, 0, ILI9488_RDCOLMOD, 0x00, 0x55,
  2, 0, ILI9488_MADCTL, 0x48,
  2, 0, ILI9488_COLMOD, 0x55,
  1, 120, ILI9488_INVON,
  1, 120, ILI9488_DISPON,
  0
};

static const uint8_t ILI9481_2_init_commands[] = {
  1, 150, 0x01,
  2, 150, 0x11,
  3, 150, 0xd0, 0x07, 0x44, 0x1E,
  3, 0, 0xd1, 0x00, 0x0C, 0x1A ,
  4, 0, 0xC5, 0x03,
  3, 0, 0xd2, 0x01, 0x11,
  2, 0, 0xE4, 0xa0,
  3, 0, 0xf3, 0x00, 0x2a,
  13, 0, 0xc8,	0x00,	0x26,	0x21,	0x00,	0x00,	0x1f,	0x65,	0x23,	0x77,	0x00,	0x0f,	0x00,
  6, 0, 0xC0, 0x00, 0x3B, 0x00, 0x02, 0x11 ,
  2, 0, 0xc6, 0x83,
  2, 0, 0xf0, 0x01,
  2, 0, 0xE4, 0xa0,
  2, 0, 0x36, 0x8C,
  2, 0, 0x3a, 0x55,
  5, 255, 0xb4, 0x02, 0x00, 0x00, 0x01,
  5, 0, 0x2a,	0x00,	0x00,	0x01, 0x3F,
  5, 10, 0x2b, 0x00, 0x00, 0x01, 0xDf,
  1, 0, 0x29,
  1, 120, 0x2c,
  0
};


static const uint8_t R61519_init_commands[] = {
  1, 120, 0x01,
  1, 20, 0x11,
  2, 2, 0xB0, 0x04,
  16, 0, 0xB8,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  5, 0, 0xB9,0x01,0x00,0xff,0x18,
  6, 2, 0xB3, 0x00, 0x00, 0x00, 0x00,
  2, 0, 0xB4, 0x00,
  9, 0, 0xC0,0x03,0xDF,0x40,0x10,0x00,0x01,0x00,0x55,
  6, 0, 0xC1,0x07,0x27,0x08,0x08,0x00,
  5, 0, 0xC4,0x57,0x00,0x05,0x03,
  2, 0, 0xC6, 0x04,
  25, 0, 0xC8,0x03,0x12,0x1A,0x24,0x32,0x4B,0x3B,0x29,0x1F,0x18,0x12,0x04,0x03,0x12,0x1A,0x24,0x32,0x4B,0x3B,0x29,0x1F,0x18,0x12,0x04,
  25, 0, 0xC9,0x03,0x12,0x1A,0x24,0x32,0x4B,0x3B,0x29,0x1F,0x18,0x12,0x04,0x03,0x12,0x1A,0x24,0x32,0x4B,0x3B,0x29,0x1F,0x18,0x12,0x04,
  25, 0, 0xCA,0x03,0x12,0x1A,0x24,0x32,0x4B,0x3B,0x29,0x1F,0x18,0x12,0x04,0x03,0x12,0x1A,0x24,0x32,0x4B,0x3B,0x29,0x1F,0x18,0x12,0x04,
  17, 0, 0xD0,0x99,0x06,0x08,0x20,0x29,0x04,0x01,0x00,0x08,0x01,0x00,0x06,0x01,0x00,0x00, 0x20,
  5, 0, 0xD1,0x00,0x20,0x20,0x15,
  5, 0, 0xE0, 0x00,0x00,0x00,0x00,
  7, 0, 0xE1, 0x00,0x00,0x00,0x00,0x00,0x00,
  2, 0, 0xE2, 0x00,
  2, 0, 0x3A, 0x55,
  5, 0, 0x2A, 0x00,0x00,0x01,0x3F,
  5, 120, 0x2B,0x00,0x00,0x01,0xDF,
  1, 120, 0x29,
  0
};

//--------------------------------------------------

#ifdef __cplusplus
class ILI948x_t4_mm : public Teensy_Parallel_GFX {
  public:
    ILI948x_t4_mm(int8_t dc, int8_t cs = -1, int8_t rst = -1);
    void begin(uint8_t display_name = ILI9488, uint8_t buad_div = 20);
    uint8_t getBusSpd();

    uint8_t setBitDepth(uint8_t bitDepth);
    uint8_t getBitDepth();

    void setFrameRate(uint8_t frRate);
    uint8_t getFrameRate();

    void setTearingEffect(bool tearingOn);
    bool getTearingEffect();

    void setTearingScanLine(uint16_t scanLine);
    uint16_t getTearingScanLine();

    void setRotation(uint8_t r);
    void invertDisplay(bool invert);
    void displayInfo();
    void setAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

    void pushPixels16bit(const uint16_t *pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    void pushPixels16bitDMA(const uint16_t *pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

    uint8_t readCommand(uint8_t const cmd);
    uint32_t readCommandN(uint8_t const cmd, uint8_t count_bytes);

    // Added functions to read pixel data...
    uint16_t readPixel(int16_t x, int16_t y);
    void readRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pcolors);

    // void pushPixels16bitTearing(uint16_t * pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
    // void pushPixels24bitTearing(uint16_t * pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2 );
    void DMAerror();

    /**************************************************************/
    void setScroll(uint16_t offset);
    
    uint16_t _previous_addr_x0 = 0xffff;
    uint16_t _previous_addr_x1 = 0xffff;
    uint16_t _previous_addr_y0 = 0xffff;
    uint16_t _previous_addr_y1 = 0xffff;

    void setAddr(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
        __attribute__((always_inline)) {

        uint8_t Command;
        uint8_t CommandValue[4];
        if ((x0 != _previous_addr_x0) || (x1 != _previous_addr_x1)) {
            Command = 0x2A;
            CommandValue[0U] = x0 >> 8U;
            CommandValue[1U] = x0 & 0xFF;
            CommandValue[2U] = x1 >> 8U;
            CommandValue[3U] = x1 & 0xFF;
            SglBeatWR_nPrm_8(Command, CommandValue, 4U);
            _previous_addr_x0 = x0;
            _previous_addr_x1 = x1;
        }
        if ((y0 != _previous_addr_y0) || (y1 != _previous_addr_y1)) {
            Command = 0x2B;
            CommandValue[0U] = y0 >> 8U;
            CommandValue[1U] = y0 & 0xFF;
            CommandValue[2U] = y1 >> 8U;
            CommandValue[3U] = y1 & 0xFF;
            SglBeatWR_nPrm_8(Command, CommandValue, 4U);
            _previous_addr_y0 = y0;
            _previous_addr_y1 = y1;
        }
    }

    // kurts experiment
    void beginWrite16BitColors();
    void write16BitColor(uint16_t color);
    void endWrite16BitColors();
    void write16BitColor(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const uint16_t *pcolors, uint16_t count);

    typedef void (*CBF)();
    CBF _callback;
    void onCompleteCB(CBF callback);

  protected:
  private:
    uint8_t _display_name = 0;
    FlexIOHandler *pFlex;
    IMXRT_FLEXIO_t *p;
    const FlexIOHandler::FLEXIO_Hardware_t *hw;
    static DMAChannel flexDma;

    uint8_t _buad_div = 20;

    uint8_t _bitDepth = 16;
    uint8_t _rotation = 0;
    uint8_t MADCTL[5];

    uint8_t _frameRate = 60;

    bool _bTearingOn = false;
    uint16_t _tearingScanLine = 0;

    // int16_t _width, _height;
    int8_t _dc, _cs, _rst;

    uint8_t _dummy;
    uint8_t _curMADCTL;

    uint16_t _lastx1, _lastx2, _lasty1, _lasty2;

    volatile bool WR_DMATransferDone = true;
    uint32_t MulBeatCountRemain;
    uint16_t *MulBeatDataRemain;
    uint32_t TotalSize;

    void displayInit(uint8_t display_name);
    void CSLow();
    void CSHigh();
    void DCLow();
    void DCHigh();
    void gpioWrite();
    void gpioRead();

    void FlexIO_Init();
    void FlexIO_Config_SnglBeat();
    void FlexIO_Clear_Config_SnglBeat();
    void FlexIO_Config_MultiBeat();
    void FlexIO_Config_SnglBeat_Read();

    void SglBeatWR_nPrm_8(uint32_t const cmd, uint8_t const *value, uint32_t const length);
    void SglBeatWR_nPrm_16(uint32_t const cmd, const uint16_t *value, uint32_t const length);
    void MulBeatWR_nPrm_DMA(uint32_t const cmd, const void *value, uint32_t const length);

    void microSecondDelay();

    static void dmaISR();
    void flexDma_Callback();

    bool isCB = false;
    void _onCompleteCB();

    static ILI948x_t4_mm *dmaCallback;
};
#endif //__cplusplus
#endif //_IILI948x_t4_mm_H_