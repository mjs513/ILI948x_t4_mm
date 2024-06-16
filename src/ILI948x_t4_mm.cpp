#include "ILI948x_t4_mm.h"
#include "ILI948x_t4_mm_default_flexio_pins.h"

// DMAMEM uint32_t framebuff[DATABUFBYTES];

#if !defined(ARDUINO_TEENSY_MICROMOD)
#warning This library only supports the Teensy Micromod!
#endif

//--------------------------------------------------
PROGMEM const uint8_t ILI9488_init_commands[] = {
    1, 120, 0x01, // SW RST
    1, 15, 0x11,  // Exit sleep
    1, 15, 0x28,  // Display Off
    3, 0, 0xC0, 0x19, 0x1A,
    3, 0, 0xC1, 0x45, 0x00,
    2, 0, 0xC2, 0x33,
    4, 0, 0xC5, 0x00, 0x12, 0x80,
    2, 0, 0xB4, 0x02,
    4, 0, 0xB6, 0x00, 0x02, 0x3B,
    2, 0, 0xB7, 0x07,
    16, 0, 0xE0, 0x00, 0x03, 0x09, 0x08, 0x16, 0x0A, 0x3F, 0x78, 0x4C, 0x09, 0x0A, 0x08, 0x16, 0x1A, 0x0F,
    16, 0, 0xE1, 0x00, 0x16, 0x19, 0x03, 0x0F, 0x05, 0x32, 0x45, 0x46, 0x04, 0x0E, 0x0D, 0x35, 0x37, 0x0F,
    2, 10, 0x36, 0x48,
    1, 120, 0x29, // Display On
    0};

PROGMEM const uint8_t ILI9486_init_commands[] = {
    1, 120, 0x01,
    1, 20, 0x11, // Sleep out, also SW reset
    2, 0, 0x3A, 0x55,
    2, 0, 0xC2, 0x44,
    5, 0, 0xC5, 0x00, 0x00, 0x00, 0x00,
    16, 0, 0xE0, 0x0F, 0x1F, 0x1C, 0x0C, 0x0C, 0x08, 0x48, 0x98, 0x37, 0x0A, 0x13, 0x04, 0x11, 0x0D, 0x00,
    16, 0, 0xE1, 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75, 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00,
    2, 0, 0x36, 0x48,
    1, 0, 0x20,
    1, 120, 0x29, // Display ON
    0};

PROGMEM const uint8_t ILI9481_1_init_commands[] = {
    1, 120, ILI9488_SWRESET,
    1, 20, ILI9488_SLPOUT,
    4, 0, ILI9488_NVMEMWR, 0x07, 0x41, 0x1D,
    4, 0, ILI9488_NVMEMPROTKEY, 0x00, 0x2B, 0x1F,
    3, 0, ILI9488_NVMEMSTATRD, 0x01, 0x11,
    7, 0, ILI9488_PWCTR1, 0x10, 0x3B, 0x00, 0x02, 0x11, 0x00,
    2, 0, ILI9488_VMCTR1, 0x03,
    2, 0, ILI9488_CABCCTRL1, 0x80,
    13, 0, ILI9488_CABCCTRL2, 0x00, 0x14, 0x33, 0x10, 0x00, 0x16, 0x44, 0x36, 0x77, 0x00, 0x0F, 0x00,
    2, 0, 0xB0, 0x00,
    2, 0, 0xE4, 0xA0,
    2, 0, 0xF0, 0x08,
    3, 0, 0xF3, 0x40, 0x0A,
    1, 0, 0xF6, 0x84,
    1, 0, ILI9488_ADJCTL3, 0x80,
    5, 0, ILI9488_FRMCTR3, 0x00, 0x01, 0x06, 0x30,
    1, 0, ILI9488_INVCTR, 0x00,
    2, 0, ILI9488_RDCOLMOD, 0x00, 0x55,
    2, 0, ILI9488_MADCTL, 0x48,
    2, 0, ILI9488_COLMOD, 0x55,
    1, 120, ILI9488_INVON,
    1, 120, ILI9488_DISPON,
    0};

PROGMEM const uint8_t ILI9481_2_init_commands[] = {
    1, 150, 0x01,
    2, 150, 0x11,
    3, 150, 0xd0, 0x07, 0x44, 0x1E,
    3, 0, 0xd1, 0x00, 0x0C, 0x1A,
    4, 0, 0xC5, 0x03,
    3, 0, 0xd2, 0x01, 0x11,
    2, 0, 0xE4, 0xa0,
    3, 0, 0xf3, 0x00, 0x2a,
    13, 0, 0xc8, 0x00, 0x26, 0x21, 0x00, 0x00, 0x1f, 0x65, 0x23, 0x77, 0x00, 0x0f, 0x00,
    6, 0, 0xC0, 0x00, 0x3B, 0x00, 0x02, 0x11,
    2, 0, 0xc6, 0x83,
    2, 0, 0xf0, 0x01,
    2, 0, 0xE4, 0xa0,
    2, 0, 0x36, 0x8C,
    2, 0, 0x3a, 0x55,
    5, 255, 0xb4, 0x02, 0x00, 0x00, 0x01,
    5, 0, 0x2a, 0x00, 0x00, 0x01, 0x3F,
    5, 10, 0x2b, 0x00, 0x00, 0x01, 0xDf,
    1, 0, 0x29,
    1, 120, 0x2c,
    0};

PROGMEM const uint8_t R61519_init_commands[] = {
    1, 120, 0x01,
    1, 20, 0x11,
    2, 2, 0xB0, 0x04,
    16, 0, 0xB8, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    5, 0, 0xB9, 0x01, 0x00, 0xff, 0x18,
    6, 2, 0xB3, 0x00, 0x00, 0x00, 0x00,
    2, 0, 0xB4, 0x00,
    9, 0, 0xC0, 0x03, 0xDF, 0x40, 0x10, 0x00, 0x01, 0x00, 0x55,
    6, 0, 0xC1, 0x07, 0x27, 0x08, 0x08, 0x00,
    5, 0, 0xC4, 0x57, 0x00, 0x05, 0x03,
    2, 0, 0xC6, 0x04,
    25, 0, 0xC8, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04,
    25, 0, 0xC9, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04,
    25, 0, 0xCA, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04, 0x03, 0x12, 0x1A, 0x24, 0x32, 0x4B, 0x3B, 0x29, 0x1F, 0x18, 0x12, 0x04,
    17, 0, 0xD0, 0x99, 0x06, 0x08, 0x20, 0x29, 0x04, 0x01, 0x00, 0x08, 0x01, 0x00, 0x06, 0x01, 0x00, 0x00, 0x20,
    5, 0, 0xD1, 0x00, 0x20, 0x20, 0x15,
    5, 0, 0xE0, 0x00, 0x00, 0x00, 0x00,
    7, 0, 0xE1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    2, 0, 0xE2, 0x00,
    2, 0, 0x3A, 0x55,
    5, 0, 0x2A, 0x00, 0x00, 0x01, 0x3F,
    5, 120, 0x2B, 0x00, 0x00, 0x01, 0xDF,
    1, 120, 0x29,
    0};

//--------------------------------------------------

FLASHMEM ILI948x_t4_mm::ILI948x_t4_mm(int8_t dc, int8_t cs, int8_t rst)
    : Teensy_Parallel_GFX(_TFTWIDTH, _TFTHEIGHT), _dc(dc), _cs(cs), _rst(rst),
      _data_pins{DISPLAY_D0, DISPLAY_D1, DISPLAY_D2, DISPLAY_D3, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7},
      _wr_pin(DISPLAY_WR), _rd_pin(DISPLAY_RD) {
}

FLASHMEM void ILI948x_t4_mm::begin(uint8_t display_name, uint8_t buad_div) {
    // Serial.printf("Bus speed: %d Mhz \n", buad_div);

    _display_name = display_name;

    switch (buad_div) {
    case 2:
        _buad_div = 120;
        break;
    case 4:
        _buad_div = 60;
        break;
    case 8:
        _buad_div = 30;
        break;
    case 12:
        _buad_div = 20;
        break;
    case 20:
        _buad_div = 12;
        break;
    case 24:
        _buad_div = 10;
        break;
    case 30:
        _buad_div = 8;
        break;
    case 40:
        _buad_div = 6;
        break;
    default:
        _buad_div = 20; // 12Mhz
        break;
    }
    Serial.printf("Bus speed: %d Mhz Div: %d\n", buad_div, _buad_div);
    pinMode(_cs, OUTPUT);  // CS
    pinMode(_dc, OUTPUT);  // DC
    pinMode(_rst, OUTPUT); // RST

    *(portControlRegister(_cs)) = 0xFF;
    *(portControlRegister(_dc)) = 0xFF;
    *(portControlRegister(_rst)) = 0xFF;

    digitalWriteFast(_cs, HIGH);
    digitalWriteFast(_dc, HIGH);
    digitalWriteFast(_rst, HIGH);

    delay(15);
    digitalWrite(_rst, LOW);
    delay(15);
    digitalWriteFast(_rst, HIGH);
    delay(100);

    FlexIO_Init();

    displayInit(display_name);
    /*
    setBitDepth(_bitDepth);

    setTearingEffect(_bTearingOn);
    if (_bTearingOn == true) {
      setTearingScanLine(_tearingScanLine);
    }
    setFrameRate(_frameRate);
    */

    _width = _TFTWIDTH;
    _height = _TFTHEIGHT;

    setClipRect();
    setOrigin();
    setTextSize(1);
}

FLASHMEM uint8_t ILI948x_t4_mm::setBitDepth(uint8_t bitDepth) {
    uint8_t bd;

    switch (bitDepth) {
    case 16:
        _bitDepth = 16;
        bd = 0x55;
        break;
    case 18:
        _bitDepth = 18;
        bd = 0x66;
        break;
    case 24: // Unsupported
        return _bitDepth;
        break;
    default: // Unsupported
        return _bitDepth;
        break;
    }

    SglBeatWR_nPrm_8(ILI9488_COLMOD, &bd, 1);

    // Insert small delay here as rapid calls appear to fail
    delay(10);

    return _bitDepth;
}

FLASHMEM uint8_t ILI948x_t4_mm::getBitDepth() {
    return _bitDepth;
}

FLASHMEM void ILI948x_t4_mm::setFrameRate(uint8_t frRate) {
    _frameRate = frRate;

    uint8_t fr28Hz[2] = {0x00, 0x11}; // 28.78fps, 17 clocks
    uint8_t fr30Hz[2] = {0x10, 0x11}; // 30.38fps, 17 clocks
    uint8_t fr39Hz[2] = {0x50, 0x11}; // 39.06fps, 17 clocks
    uint8_t fr45Hz[2] = {0x70, 0x11}; // 45.57fps, 17 clocks
    uint8_t fr54Hz[2] = {0x90, 0x11}; // 54.69ps, 17 clocks
    uint8_t fr60Hz[2] = {0xA0, 0x11}; // 60.76fps, 17 clocks
    uint8_t fr68Hz[2] = {0xB0, 0x11}; // 68.36fps, 17 clocks (ILI9488 default)
    uint8_t fr78Hz[2] = {0xC0, 0x11}; // 78.13fps, 17 clocks
    uint8_t fr91Hz[2] = {0xD0, 0x11}; // 91.15fps, 17 clocks

    uint8_t frData[2];
    // Select parameters for frame rate
    switch (frRate) {
    case 28:
        memcpy(frData, fr28Hz, sizeof fr28Hz);
        break;
    case 30:
        memcpy(frData, fr30Hz, sizeof fr30Hz);
        break;
    case 39:
        memcpy(frData, fr39Hz, sizeof fr39Hz);
        break;
    case 45:
        memcpy(frData, fr45Hz, sizeof fr45Hz);
        break;
    case 54:
        memcpy(frData, fr54Hz, sizeof fr54Hz);
        break;
    case 60:
        memcpy(frData, fr60Hz, sizeof fr60Hz);
        break;
    case 68:
        memcpy(frData, fr68Hz, sizeof fr68Hz);
        break;
    case 78:
        memcpy(frData, fr78Hz, sizeof fr78Hz);
        break;
    case 91:
        memcpy(frData, fr91Hz, sizeof fr91Hz);
        break;
    default:
        memcpy(frData, fr60Hz, sizeof fr60Hz);
        _frameRate = 60;
        break;
    }

    SglBeatWR_nPrm_8(ILI9488_FRMCTR1, frData, 2);
}

FLASHMEM uint8_t ILI948x_t4_mm::getFrameRate() {
    return _frameRate;
}

FLASHMEM void ILI948x_t4_mm::setTearingEffect(bool tearingOn) {

    _bTearingOn = tearingOn;
    uint8_t mode = 0x00;

    CSLow();
    if (_bTearingOn == true) {
        SglBeatWR_nPrm_8(ILI9488_TEON, &mode, 1); // Tearing effect line on, mode 0 (V-Blanking)
    } else {
        SglBeatWR_nPrm_8(ILI9488_TEOFF, 0, 0);
    }
    CSHigh();
}

FLASHMEM bool ILI948x_t4_mm::getTearingEffect() {
    return _bTearingOn;
}

FLASHMEM void ILI948x_t4_mm::setTearingScanLine(uint16_t scanLine) {
    _tearingScanLine = scanLine;

    uint8_t params[2] = {(uint8_t)(_tearingScanLine << 8), (uint8_t)(_tearingScanLine & 0xFF)};
    SglBeatWR_nPrm_8(ILI9488_TESLWR, params, 2); // Tearing effect write scan line : 0x00 0x00 = line 0 (default), 0x00 0xA0 = line 160, 0x00 0xF0 = line 240
}

FLASHMEM uint16_t ILI948x_t4_mm::getTearingScanLine() {
    return _tearingScanLine;
}

FLASHMEM void ILI948x_t4_mm::setRotation(uint8_t r) {
    _rotation = r & 3;

    switch (_rotation) {
    case 0:
    case 2:
        _width = _TFTWIDTH;
        _height = _TFTHEIGHT;
        break;
    case 1:
    case 3:
        _width = _TFTHEIGHT;
        _height = _TFTWIDTH;
        break;
    }

    setClipRect();
    setOrigin();

    cursor_x = 0;
    cursor_y = 0;

    SglBeatWR_nPrm_8(ILI9488_MADCTL, &MADCTL[_rotation], 1);
}

FLASHMEM void ILI948x_t4_mm::invertDisplay(bool invert) {
    SglBeatWR_nPrm_8(invert ? ILI9488_INVON : ILI9488_INVOFF, 0, 0);
}

void ILI948x_t4_mm::setScroll(uint16_t offset) {
    //   SglBeatWR_nPrm_8(ILI9488_VSCRSADD, offset, 1); // Changed, offset is
    SglBeatWR_nPrm_16(ILI9488_VSCRSADD, &offset, 1); // a pointer to a 16 bit value.
}

FLASHMEM void ILI948x_t4_mm::onCompleteCB(CBF callback) {
    _callback = callback;
    isCB = true;
}

FASTRUN void ILI948x_t4_mm::setAddrWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    uint8_t Command;
    uint8_t CommandValue[4];

    Command = 0x2A;
    CommandValue[0U] = x1 >> 8U;
    CommandValue[1U] = x1 & 0xFF;
    CommandValue[2U] = x2 >> 8U;
    CommandValue[3U] = x2 & 0xFF;
    SglBeatWR_nPrm_8(Command, CommandValue, 4U);

    Command = 0x2B;
    CommandValue[0U] = y1 >> 8U;
    CommandValue[1U] = y1 & 0xFF;
    CommandValue[2U] = y2 >> 8U;
    CommandValue[3U] = y2 & 0xFF;
    SglBeatWR_nPrm_8(Command, CommandValue, 4U);
}

FASTRUN void ILI948x_t4_mm::displayInfo() {
    CSLow();
    Serial.printf("Manufacturer ID: 0x%02X\n", readCommand(ILI9488_RDID1));
    Serial.printf("Module Version ID: 0x%02X\n", readCommand(ILI9488_RDID2));
    Serial.printf("Module ID: 0x%02X\n", readCommand(ILI9488_RDID3));
    Serial.printf("Display Power Mode: 0x%02X\n", readCommand(ILI9488_RDMODE));
    Serial.printf("MADCTL Mode: 0x%02X\n", readCommand(ILI9488_RDMADCTL));
    Serial.printf("Pixel Format: 0x%02X\n", readCommand(ILI9488_RDCOLMOD));
    Serial.printf("Image Format: 0x%02X\n", readCommand(ILI9488_RDIMGFMT));
    Serial.printf("Signal Mode: 0x%02X\n", readCommand(ILI9488_RDDSM));
    uint8_t sdRes = readCommand(ILI9488_RDSELFDIAG);
    Serial.printf("Self Diagnostic: %s (0x%02X)\n", sdRes == 0xc0 ? "OK" : "Failed", sdRes);
    Serial.printf("Device Information: %06X\n", readCommandN(ILI9488_RDDID, 3));
    uint32_t device_status = readCommandN(ILI9488_RDDST, 4);
    Serial.printf("Device Status: %08X\n", device_status);
    Serial.printf("\tOrder: %s\n", (device_status & (1 << 26)) ? "BGR" : "RGB");
    Serial.print("\tinterface pixel format: ");
    switch ((device_status >> 20) & 0x7) {
    case 0x5:
        Serial.println("16 bit");
        break;
    case 0x6:
        Serial.println("18 bit");
        break;
    case 0x7:
        Serial.println("24 bit");
        break;
    default:
        Serial.println("????");
    }

    CSHigh();
}

FASTRUN void ILI948x_t4_mm::pushPixels16bit(const uint16_t *pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    while (WR_DMATransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    uint32_t area = (x2 - x1 + 1) * (y2 - y1 + 1);
    if (!((_lastx1 == x1) && (_lastx2 == x2) && (_lasty1 == y1) && (_lasty2 == y2))) {
        setAddrWindow(x1, y1, x2, y2);
        _lastx1 = x1;
        _lastx2 = x2;
        _lasty1 = y1;
        _lasty2 = y2;
    }
    SglBeatWR_nPrm_16(ILI9488_RAMWR, pcolors, area);
}

FASTRUN void ILI948x_t4_mm::pushPixels16bitDMA(const uint16_t *pcolors, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    while (WR_DMATransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    uint32_t area = (x2 - x1 + 1) * (y2 - y1 + 1);
    if (!((_lastx1 == x1) && (_lastx2 == x2) && (_lasty1 == y1) && (_lasty2 == y2))) {
        setAddrWindow(x1, y1, x2, y2);
        _lastx1 = x1;
        _lastx2 = x2;
        _lasty1 = y1;
        _lasty2 = y2;
    }

    MulBeatWR_nPrm_DMA(ILI9488_RAMWR, pcolors, area);
}

///////////////////
// Private functions
///////////////////
FLASHMEM void ILI948x_t4_mm::displayInit(uint8_t disp_name) {
    const uint8_t *addr;
    Serial.println("displayInit called");
    switch (disp_name) {
    case 2: // ILI9481-1
    {
        addr = ILI9481_1_init_commands;

        MADCTL[0] = MADCTL_BGR | MADCTL_SS;
        MADCTL[1] = MADCTL_MV | MADCTL_BGR;
        MADCTL[2] = MADCTL_BGR | MADCTL_GS;
        MADCTL[3] = MADCTL_MV | MADCTL_BGR | MADCTL_SS | MADCTL_GS;
        Serial.println("ILI9481 Initialized");
    } break;
    case 3: // ILI9481_2
    {
        addr = ILI9481_2_init_commands;

        MADCTL[0] = MADCTL_BGR | MADCTL_SS;
        MADCTL[1] = MADCTL_MV | MADCTL_BGR;
        MADCTL[2] = MADCTL_BGR | MADCTL_GS;
        MADCTL[3] = MADCTL_MV | MADCTL_BGR | MADCTL_SS | MADCTL_GS;
        Serial.println("ILI9481 Initialized");

    } break;
    case 1: // ILI9486
    {
        addr = ILI9486_init_commands;

        MADCTL[0] = MADCTL_MX | MADCTL_BGR;
        MADCTL[1] = MADCTL_MV | MADCTL_BGR;
        MADCTL[2] = MADCTL_MY | MADCTL_BGR;
        MADCTL[3] = MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR;
        MADCTL[4] = MADCTL_MY | MADCTL_MV | MADCTL_BGR;
        Serial.println("ILI9486 Initialized");
    } break;

    case 4: {
        addr = R61519_init_commands;

        MADCTL[0] = MADCTL_RGB;
        MADCTL[1] = MADCTL_MV | MADCTL_MX | MADCTL_RGB;
        MADCTL[2] = MADCTL_RGB | MADCTL_GS | MADCTL_MX;
        MADCTL[3] = MADCTL_MV | MADCTL_RGB | MADCTL_GS;
        Serial.println("R61519 Initialized");
    } break;

    case 0: // ILI9488
    default: {
        addr = ILI9488_init_commands;

        MADCTL[0] = MADCTL_MX | MADCTL_BGR;
        MADCTL[1] = MADCTL_MV | MADCTL_BGR,
        MADCTL[2] = MADCTL_MY | MADCTL_BGR;
        MADCTL[3] = MADCTL_MX | MADCTL_MY | MADCTL_MV | MADCTL_BGR;
        MADCTL[4] = MADCTL_MY | MADCTL_MV | MADCTL_BGR;
        Serial.println("ILI9488 Initialized");
    } break;
    }

    uint8_t cmd, commandVals[25];
    while (1) {
        uint8_t count = *addr++;
        uint8_t ms = *addr++;
        if (count-- == 0)
            break;
        cmd = *addr++;
        uint8_t numArgs = 0;
        while (count-- > 0) {
            commandVals[numArgs] = *addr++;
            numArgs += 1;
        }
        // Serial.printf("CNT: %d, MS: %d, CMD: 0x%x\n", i, ms, cmd);
        // for(uint8_t j = 0; j < i; j++) {
        //   Serial.printf(" 0x%x ", commandVals[j]);
        // } Serial.println();
        SglBeatWR_nPrm_8(cmd, commandVals, numArgs);
        delay(ms);
    }
}

FASTRUN void ILI948x_t4_mm::CSLow() {
    digitalWriteFast(_cs, LOW); // Select TFT
}

FASTRUN void ILI948x_t4_mm::CSHigh() {
    digitalWriteFast(_cs, HIGH); // Deselect TFT
}

FASTRUN void ILI948x_t4_mm::DCLow() {
    digitalWriteFast(_dc, LOW); // Writing command to TFT
}

FASTRUN void ILI948x_t4_mm::DCHigh() {
    digitalWriteFast(_dc, HIGH); // Writing data to TFT
}

FASTRUN void ILI948x_t4_mm::microSecondDelay() {
    for (uint32_t i = 0; i < 99; i++)
        __asm__("nop\n\t");
}

FASTRUN void ILI948x_t4_mm::gpioWrite() {
    pFlex->setIOPinToFlexMode(_wr_pin);
    pinMode(_rd_pin, OUTPUT);
    digitalWriteFast(_rd_pin, HIGH);
}

FASTRUN void ILI948x_t4_mm::gpioRead() {
    pFlex->setIOPinToFlexMode(_rd_pin);
    pinMode(_wr_pin, OUTPUT);
    digitalWriteFast(_wr_pin, HIGH);
}

// If used this must be called before begin
// Set the FlexIO pins.  The first version you can specify just the wr, and read and optionsl first Data.
// it will use information in the Flexio library to fill in d1-d7
FASTRUN bool ILI948x_t4_mm::setFlexIOPins(uint8_t write_pin, uint8_t rd_pin, uint8_t tft_d0) {
    Serial.printf("ILI948x_t4_mm::setFlexIOPins(%u, %u, %u) %u %u %u\n", write_pin, rd_pin, tft_d0, _data_pins[0], _wr_pin, _rd_pin);
    Serial.flush();
    if (tft_d0 != 0xff) {
#ifdef FLEX_IO_HAS_FULL_PIN_MAPPING
        Serial.println("\td0 != 0xff\n");

        uint8_t flexio_pin;
        pFlex = FlexIOHandler::mapIOPinToFlexIOHandler(tft_d0, flexio_pin);
        if ((pFlex == nullptr) || (flexio_pin == 0xff))
            return false;

        _data_pins[0] = tft_d0;

        // lets dos some quick validation of the pins.
        for (uint8_t i = 1; i < 8; i++) {
            flexio_pin++; // lets look up the what pins come next.
            _data_pins[i] = pFlex->mapFlexPinToIOPin(flexio_pin);
            if (_data_pins[i] == 0xff) {
                Serial.printf("Failed to find Teensy IO pin for Flexio pin %u\n", flexio_pin);
                return false;
            }
        }
#else
        return false;
#endif
    }
    // set the write and read pins and see if d0 is not 0xff set it and compute the others.
    if (write_pin != 0xff)
        _wr_pin = write_pin;
    if (rd_pin != 0xff)
        _rd_pin = rd_pin;

     Serial.printf("FlexIO pins: data: %u %u %u %u %u %u %u %u WR:%u RD:%u\n",
                   _data_pins[0], _data_pins[1], _data_pins[2], _data_pins[3], _data_pins[4], _data_pins[5], _data_pins[6], _data_pins[7],
                   _wr_pin, _rd_pin);
    return true;
}

// Set the FlexIO pins.  Specify all of the pins for 8 bit mode. Must be called before begin
FLASHMEM bool ILI948x_t4_mm::setFlexIOPins(uint8_t write_pin, uint8_t rd_pin, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                                           uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {

    _data_pins[0] = d0;
    _data_pins[1] = d1;
    _data_pins[2] = d2;
    _data_pins[3] = d3;
    _data_pins[4] = d4;
    _data_pins[5] = d5;
    _data_pins[6] = d6;
    _data_pins[7] = d7;
    _wr_pin = write_pin;
    _rd_pin = rd_pin;

    Serial.printf("FlexIO pins: data: %u %u %u %u %u %u %u %u WR:%u RD:%u\n",
                  _data_pins[0], _data_pins[1], _data_pins[2], _data_pins[3], _data_pins[4], _data_pins[5], _data_pins[6], _data_pins[7],
                  _wr_pin, _rd_pin);
    // Note this does not verify the pins are valid.
    return true;
}

FASTRUN void ILI948x_t4_mm::FlexIO_Init() {
    /* Get a FlexIO channel */
    // lets assume D0 is the valid one...
    Serial.printf("FlexIO_Init: D0:%u WR:%u RD:%u\n", _data_pins[0], _wr_pin, _rd_pin);
    Serial.flush();
    pFlex = FlexIOHandler::mapIOPinToFlexIOHandler(_data_pins[0], _flexio_D0);
    // pFlex = FlexIOHandler::flexIOHandler_list[1]; // use FlexIO2
    /* Pointer to the port structure in the FlexIO channel */
    p = &pFlex->port();
    /* Pointer to the hardware structure in the FlexIO channel */
    hw = &pFlex->hardware();

    // lets dos some quick validation of the pins.
    for (uint8_t i = 1; i < 8; i++) {
        uint8_t flexio_pin = pFlex->mapIOPinToFlexPin(_data_pins[i]);
        if (flexio_pin != (_flexio_D0 + i)) {
            Serial.printf("ILI948x_t4_mm::FlexIO_Ini - Flex IO Data pins pin issue D0(%u), D%u(%u)\n", _flexio_D0, i, flexio_pin);
        }
    }

    // Lets reserve the timer and shifters.
    _flexio_timer = pFlex->requestTimers();
    _flexio_timer_mask = 1 << _flexio_timer;

    if (pFlex->claimShifter(0)) {
        _write_shifter = 0;
    } else if (pFlex->claimShifter(4)) {
        _write_shifter = 4;
    } else {
        Serial.println("ILI948x_t4_mm::FlexIO_Init could not claim write Timer(0 or 4");
    }

    // Maybe this is optional
    if (pFlex->claimShifter(3)) {
        _read_shifter = 3;
    } else if (pFlex->claimShifter(7)) {
        _read_shifter = 7;
    } else {
        Serial.println("ILI948x_t4_mm::FlexIO_Init could not claim Read Timer(3 or 7");
    }
    _write_shifter_mask = 1 << _write_shifter;
    _read_shifter_mask = 1 << _read_shifter;

    Serial.printf("FlexIO Timer:%u Shifter Write:%u Read:%u\n", _flexio_timer, _write_shifter, _read_shifter);

    _flexio_WR = pFlex->mapIOPinToFlexPin(_wr_pin);
    _flexio_RD = pFlex->mapIOPinToFlexPin(_rd_pin);

    if ((_flexio_WR == 0xff) || (_flexio_RD == 0xff)) {
        Serial.printf("ILI948x_t4_mm::FlexIO_Ini - RD/WR pin issue: WR:%u(%u) RD:%u(%u)\n", _wr_pin, _flexio_WR, _rd_pin, _flexio_RD);
    }

    Serial.printf("FlexIO pin mappings: D0(%u)=%u  WR(%u)=%u RD(%u)=%u\n)", _data_pins[0], _flexio_D0, _wr_pin, _flexio_WR, _rd_pin, _flexio_RD);

    // Now l

    /* Basic pin setup */
    pinMode(_wr_pin, OUTPUT); // FlexIO2:0 WR
    pinMode(_rd_pin, OUTPUT); // FlexIO2:1 RD

    for (uint8_t pin_index = 0; pin_index < 8; pin_index++) {
        pinMode(_data_pins[pin_index], OUTPUT);
        *(portControlRegister(_data_pins[pin_index])) = 0xFF;
        pFlex->setIOPinToFlexMode(_data_pins[pin_index]);
    }

    digitalWriteFast(_wr_pin, HIGH);
    *(portControlRegister(_wr_pin)) = 0xFF;

    /* High speed and drive strength configuration */
    *(portControlRegister(_rd_pin)) = 0xFF;

    /* Set clock */
    pFlex->setClockSettings(3, 1, 0); // (480 MHz source, 1+1, 1+0) >> 480/2/1 >> 240Mhz

    // Read pin starts off as normal IO pin.
    digitalWriteFast(_rd_pin, HIGH);

    /* Enable the clock */
    hw->clock_gate_register |= hw->clock_gate_mask;
    /* Enable the FlexIO with fast access */
    p->CTRL = FLEXIO_CTRL_FLEXEN | FLEXIO_CTRL_FASTACC;

    Serial.println("*** flexio_init completed ***");
}

FASTRUN void ILI948x_t4_mm::FlexIO_Config_SnglBeat_Read() {

    if (flex_config == CONFIG_SNGLREAD) return;
    flex_config = CONFIG_SNGLREAD;

    p->CTRL &= ~FLEXIO_CTRL_FLEXEN;
    //p->CTRL |= FLEXIO_CTRL_SWRST;
    //p->CTRL &= ~FLEXIO_CTRL_SWRST;

    gpioRead(); // write line high, pin 12(rst) as output

    /* Configure the shifters */
    p->SHIFTCFG[_read_shifter] =
        // FLEXIO_SHIFTCFG_INSRC                                                  /* Shifter input */
        FLEXIO_SHIFTCFG_SSTOP(0)     /* Shifter stop bit disabled */
        | FLEXIO_SHIFTCFG_SSTART(0)  /* Shifter start bit disabled and loading data on enabled */
        | FLEXIO_SHIFTCFG_PWIDTH(7); /* Bus width */

    p->SHIFTCTL[_read_shifter] =
        FLEXIO_SHIFTCTL_TIMSEL(_flexio_timer)                    /* Shifter's assigned timer index */
        | FLEXIO_SHIFTCTL_TIMPOL * (1)               /* Shift on posedge of shift clock */
        | FLEXIO_SHIFTCTL_PINCFG(0)                  /* Shifter's pin configured as input */
        | FLEXIO_SHIFTCTL_PINSEL(_flexio_D0) /*D0 */ /* Shifter's pin start index */
        | FLEXIO_SHIFTCTL_PINPOL * (0)               /* Shifter's pin active high */
        | FLEXIO_SHIFTCTL_SMOD(1);                   /* Shifter mode as recieve */

    /* Configure the timer for shift clock */
    p->TIMCMP[_flexio_timer] =
        (((1 * 2) - 1) << 8)                /* TIMCMP[15:8] = number of beats x 2 – 1 */
        | (((ILI9488_CLOCK_READ) / 2) - 1); /* TIMCMP[7:0] = baud rate divider / 2 – 1 ::: 30 = 8Mhz with current controller speed */

    p->TIMCFG[_flexio_timer] =
        FLEXIO_TIMCFG_TIMOUT(0)       /* Timer output logic one when enabled and not affected by reset */
        | FLEXIO_TIMCFG_TIMDEC(0)     /* Timer decrement on FlexIO clock, shift clock equals timer output */
        | FLEXIO_TIMCFG_TIMRST(0)     /* Timer never reset */
        | FLEXIO_TIMCFG_TIMDIS(2)     /* Timer disabled on timer compare */
        | FLEXIO_TIMCFG_TIMENA(2)     /* Timer enabled on trigger high */
        | FLEXIO_TIMCFG_TSTOP(1)      /* Timer stop bit disabled */
        | FLEXIO_TIMCFG_TSTART * (0); /* Timer start bit disabled */

    p->TIMCTL[_flexio_timer] =
        FLEXIO_TIMCTL_TRGSEL((((_read_shifter) << 2) | 1)) /* Timer trigger selected as shifter's status flag */
        | FLEXIO_TIMCTL_TRGPOL * (1)           /* Timer trigger polarity as active low */
        | FLEXIO_TIMCTL_TRGSRC * (1)           /* Timer trigger source as internal */
        | FLEXIO_TIMCTL_PINCFG(3)              /* Timer' pin configured as output */
        | FLEXIO_TIMCTL_PINSEL(_flexio_RD)     /* Timer' pin index: RD pin */
        | FLEXIO_TIMCTL_PINPOL * (1)           /* Timer' pin active low */
        | FLEXIO_TIMCTL_TIMOD(1);              /* Timer mode as dual 8-bit counters baud/bit */

    /* Enable FlexIO */
    p->CTRL |= FLEXIO_CTRL_FLEXEN;
}

FASTRUN uint8_t ILI948x_t4_mm::readCommand(uint8_t const cmd) {
    while (WR_DMATransferDone == false) {
        // Wait for any DMA transfers to complete
    }

    FlexIO_Config_SnglBeat();
    DCLow();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = cmd;

    /*Wait for transfer to be completed */
    while (0 == (p->SHIFTSTAT & _write_shifter_mask)) {
    }
    while (0 == (p->TIMSTAT & _flexio_timer_mask)) {
    }

    /* De-assert RS pin */
    microSecondDelay();
    DCHigh();

    FlexIO_Clear_Config_SnglBeat();
    FlexIO_Config_SnglBeat_Read();

    uint8_t dummy = 0;
    uint8_t data = 0;

    while (0 == (p->SHIFTSTAT & _read_shifter_mask)) {
    }
    dummy = p->SHIFTBUFBYS[_read_shifter];

    while (0 == (p->SHIFTSTAT & _read_shifter_mask)) {
    }
    data = p->SHIFTBUFBYS[_read_shifter];
    // Serial.printf("Dummy 0x%x, data 0x%x\n", dummy, data);

    // Set FlexIO back to Write mode
    FlexIO_Config_SnglBeat();
    return data;
};

// Note we could combine the above with thsi.
FASTRUN uint32_t ILI948x_t4_mm::readCommandN(uint8_t const cmd, uint8_t count_bytes) {
    while (WR_DMATransferDone == false) {
        // Wait for any DMA transfers to complete
    }

    FlexIO_Config_SnglBeat();
    DCLow();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = cmd;

    /*Wait for transfer to be completed */
    while (0 == (p->SHIFTSTAT & _write_shifter_mask)) {
    }
    while (0 == (p->TIMSTAT & _flexio_timer_mask)) {
    }

    /* De-assert RS pin */
    microSecondDelay();
    DCHigh();

    FlexIO_Clear_Config_SnglBeat();
    FlexIO_Config_SnglBeat_Read();

    uint8_t dummy = 0;
    uint32_t data = 0;

    while (0 == (p->SHIFTSTAT & _read_shifter_mask)) {
    }
    dummy = p->SHIFTBUFBYS[_read_shifter];

    while (count_bytes--) {
        while (0 == (p->SHIFTSTAT & _read_shifter_mask)) {
        }
        data = (data << 8) | (p->SHIFTBUFBYS[_read_shifter] & 0xff);
    }
    // Serial.printf("Dummy 0x%x, data 0x%x\n", dummy, data);

    // Set FlexIO back to Write mode
    FlexIO_Config_SnglBeat();
    return data;
};

void print_flexio_debug_data(FlexIOHandler *pFlex) {
    IMXRT_FLEXIO_t *p = &pFlex->port();
    Serial.println("**********************************");
    Serial.printf("FlexIO Index: %u\n", pFlex->FlexIOIndex());
    Serial.printf("CCM_CDCDR: %x\n", CCM_CDCDR);
    Serial.printf("CCM FlexIO1: %x FlexIO2: %x FlexIO3: %x\n", CCM_CCGR5 & CCM_CCGR5_FLEXIO1(CCM_CCGR_ON),
        CCM_CCGR3 & CCM_CCGR3_FLEXIO2(CCM_CCGR_ON),  CCM_CCGR7 & CCM_CCGR7_FLEXIO3(CCM_CCGR_ON));
    Serial.printf("VERID:%x PARAM:%x CTRL:%x PIN: %x\n",p->VERID,p->PARAM,p->CTRL,p->PIN);
    Serial.printf("SHIFTSTAT:%x SHIFTERR=%x TIMSTAT=%x\n",p->SHIFTSTAT,p->SHIFTERR,p->TIMSTAT);
    Serial.printf("SHIFTSIEN:%x SHIFTEIEN=%x TIMIEN=%x\n",p->SHIFTSIEN,p->SHIFTEIEN,p->TIMIEN);
    Serial.printf("SHIFTSDEN:%x SHIFTSTATE=%x\n",p->SHIFTSDEN,p->SHIFTSTATE);
    Serial.print("SHIFTCTL:");
    for(int i=0; i<8; i++){
        Serial.printf(" %08x",p->SHIFTCTL[i]);
    }
    Serial.print("\nSHIFTCFG:");
        for(int i=0; i<8; i++){
    Serial.printf(" %08x", p->SHIFTCFG[i]);
    }

    Serial.printf("\nTIMCTL:%x %x %x %x\n",p->TIMCTL[0],p->TIMCTL[1],p->TIMCTL[2],p->TIMCTL[3]);
    Serial.printf("TIMCFG:%x %x %x %x\n",p->TIMCFG[0],p->TIMCFG[1],p->TIMCFG[2],p->TIMCFG[3]);
    Serial.printf("TIMCMP:%x %x %x %x\n",p->TIMCMP[0],p->TIMCMP[1],p->TIMCMP[2],p->TIMCMP[3]);
}

FASTRUN void ILI948x_t4_mm::FlexIO_Config_SnglBeat() {

    if (flex_config == CONFIG_SNGLBEAT) return;
    flex_config = CONFIG_SNGLBEAT;

    static uint8_t DEBUG_COUNT = 2;
    static bool first_time = true;
    if (first_time) {
        first_time = false;
        Serial.print("Before setting anything");
        print_flexio_debug_data(pFlex);
    }

    p->CTRL &= ~FLEXIO_CTRL_FLEXEN;
    //p->CTRL |= FLEXIO_CTRL_SWRST;
    //p->CTRL &= ~FLEXIO_CTRL_SWRST;

    gpioWrite();

    /* Configure the shifters */
    // try setting it twice
    p->SHIFTCFG[_write_shifter] =
        FLEXIO_SHIFTCFG_INSRC * (1)  /* Shifter input */
        | FLEXIO_SHIFTCFG_SSTOP(0)   /* Shifter stop bit disabled */
        | FLEXIO_SHIFTCFG_SSTART(0)  /* Shifter start bit disabled and loading data on enabled */
        | FLEXIO_SHIFTCFG_PWIDTH(7); /* Bus width */


    p->SHIFTCTL[_write_shifter] =
        FLEXIO_SHIFTCTL_TIMSEL(_flexio_timer)            /* Shifter's assigned timer index */
        | FLEXIO_SHIFTCTL_TIMPOL * (0)       /* Shift on posedge of shift clock */
        | FLEXIO_SHIFTCTL_PINCFG(3)          /* Shifter's pin configured as output */
        | FLEXIO_SHIFTCTL_PINSEL(_flexio_D0) /* Shifter's pin start index */
        | FLEXIO_SHIFTCTL_PINPOL * (0)       /* Shifter's pin active high */
        | FLEXIO_SHIFTCTL_SMOD(2);           /* Shifter mode as transmit */

    /* Configure the timer for shift clock */
    p->TIMCMP[_flexio_timer] =
        (((1 * 2) - 1) << 8)     /* TIMCMP[15:8] = number of beats x 2 – 1 */
        | ((_buad_div / 2) - 1); /* TIMCMP[7:0] = baud rate divider / 2 – 1 */

    p->TIMCFG[_flexio_timer] =
        FLEXIO_TIMCFG_TIMOUT(0)       /* Timer output logic one when enabled and not affected by reset */
        | FLEXIO_TIMCFG_TIMDEC(0)     /* Timer decrement on FlexIO clock, shift clock equals timer output */
        | FLEXIO_TIMCFG_TIMRST(0)     /* Timer never reset */
        | FLEXIO_TIMCFG_TIMDIS(2)     /* Timer disabled on timer compare */
        | FLEXIO_TIMCFG_TIMENA(2)     /* Timer enabled on trigger high */
        | FLEXIO_TIMCFG_TSTOP(0)      /* Timer stop bit disabled */
        | FLEXIO_TIMCFG_TSTART * (0); /* Timer start bit disabled */

    p->TIMCTL[_flexio_timer] =
        FLEXIO_TIMCTL_TRGSEL((((_write_shifter) << 2) | 1)) /* Timer trigger selected as shifter's status flag */
        | FLEXIO_TIMCTL_TRGPOL * (1)           /* Timer trigger polarity as active low */
        | FLEXIO_TIMCTL_TRGSRC * (1)           /* Timer trigger source as internal */
        | FLEXIO_TIMCTL_PINCFG(3)              /* Timer' pin configured as output */
        | FLEXIO_TIMCTL_PINSEL(_flexio_WR)     /* Timer' pin index: WR pin */
        | FLEXIO_TIMCTL_PINPOL * (1)           /* Timer' pin active low */
        | FLEXIO_TIMCTL_TIMOD(1);              /* Timer mode as dual 8-bit counters baud/bit */

    
    if (DEBUG_COUNT) {
      DEBUG_COUNT--;
      print_flexio_debug_data(pFlex);
    }

    /* Enable FlexIO */
    p->CTRL |= FLEXIO_CTRL_FLEXEN;

}

FASTRUN void ILI948x_t4_mm::FlexIO_Clear_Config_SnglBeat() {
    if (flex_config == CONFIG_CLEAR) return;
    flex_config = CONFIG_CLEAR;

    p->CTRL &= ~FLEXIO_CTRL_FLEXEN;
    //p->CTRL |= FLEXIO_CTRL_SWRST;
    //p->CTRL &= ~FLEXIO_CTRL_SWRST;

    p->SHIFTCFG[_write_shifter] = 0;
    p->SHIFTCTL[_write_shifter] = 0;
    p->SHIFTSTAT = _write_shifter_mask;
    p->TIMCMP[_flexio_timer] = 0;
    p->TIMCFG[_flexio_timer] = 0;
    p->TIMSTAT = (1U << 0); /* Timer start bit disabled */
    p->TIMCTL[_flexio_timer] = 0;

    /* Enable FlexIO */
    p->CTRL |= FLEXIO_CTRL_FLEXEN;
}

FASTRUN void ILI948x_t4_mm::FlexIO_Config_MultiBeat() {
    if (flex_config == CONFIG_MULTIBEAT) return;
    flex_config = CONFIG_MULTIBEAT;

    uint32_t i;
    uint8_t MulBeatWR_BeatQty = SHIFTNUM * sizeof(uint32_t) / sizeof(uint8_t); // Number of beats = number of shifters * beats per shifter
    /* Disable and reset FlexIO */
    p->CTRL &= ~FLEXIO_CTRL_FLEXEN;
    //p->CTRL |= FLEXIO_CTRL_SWRST;
    //p->CTRL &= ~FLEXIO_CTRL_SWRST;

    gpioWrite();

    for (i = 0; i <= SHIFTNUM - 1; i++) {
        p->SHIFTCFG[i] =
            FLEXIO_SHIFTCFG_INSRC * (1U)       /* Shifter input from next shifter's output */
            | FLEXIO_SHIFTCFG_SSTOP(0U)        /* Shifter stop bit disabled */
            | FLEXIO_SHIFTCFG_SSTART(0U)       /* Shifter start bit disabled and loading data on enabled */
            | FLEXIO_SHIFTCFG_PWIDTH(8U - 1U); /* 8 bit shift width */
    }

    p->SHIFTCTL[_write_shifter] =
        FLEXIO_SHIFTCTL_TIMSEL(_flexio_timer)            /* Shifter's assigned timer index */
        | FLEXIO_SHIFTCTL_TIMPOL * (0U)      /* Shift on posedge of shift clock */
        | FLEXIO_SHIFTCTL_PINCFG(3U)         /* Shifter's pin configured as output */
        | FLEXIO_SHIFTCTL_PINSEL(_flexio_D0) /* Shifter's pin start index */
        | FLEXIO_SHIFTCTL_PINPOL * (0U)      /* Shifter's pin active high */
        | FLEXIO_SHIFTCTL_SMOD(2U);          /* shifter mode transmit */

    for (i = 1; i <= SHIFTNUM - 1; i++) {
        p->SHIFTCTL[i] =
            FLEXIO_SHIFTCTL_TIMSEL(_flexio_timer)            /* Shifter's assigned timer index */
            | FLEXIO_SHIFTCTL_TIMPOL * (0U)      /* Shift on posedge of shift clock */
            | FLEXIO_SHIFTCTL_PINCFG(0U)         /* Shifter's pin configured as output disabled */
            | FLEXIO_SHIFTCTL_PINSEL(_flexio_D0) /* Shifter's pin start index */
            | FLEXIO_SHIFTCTL_PINPOL * (0U)      /* Shifter's pin active high */
            | FLEXIO_SHIFTCTL_SMOD(2U);          /* shifter mode transmit */
    }

    /* Configure the timer for shift clock */
    p->TIMCMP[_flexio_timer] =
        ((MulBeatWR_BeatQty * 2U - 1) << 8) /* TIMCMP[15:8] = number of beats x 2 – 1 */
        | (_buad_div / 2U - 1U);            /* TIMCMP[7:0] = shift clock divide ratio / 2 - 1 */

    p->TIMCFG[_flexio_timer] = FLEXIO_TIMCFG_TIMOUT(0U)       /* Timer output logic one when enabled and not affected by reset */
                   | FLEXIO_TIMCFG_TIMDEC(0U)     /* Timer decrement on FlexIO clock, shift clock equals timer output */
                   | FLEXIO_TIMCFG_TIMRST(0U)     /* Timer never reset */
                   | FLEXIO_TIMCFG_TIMDIS(2U)     /* Timer disabled on timer compare */
                   | FLEXIO_TIMCFG_TIMENA(2U)     /* Timer enabled on trigger high */
                   | FLEXIO_TIMCFG_TSTOP(0U)      /* Timer stop bit disabled */
                   | FLEXIO_TIMCFG_TSTART * (0U); /* Timer start bit disabled */

    p->TIMCTL[_flexio_timer] =
        FLEXIO_TIMCTL_TRGSEL((_write_shifter << 2) | 1U) /* Timer trigger selected as highest shifter's status flag */
        | FLEXIO_TIMCTL_TRGPOL * (1U)       /* Timer trigger polarity as active low */
        | FLEXIO_TIMCTL_TRGSRC * (1U)       /* Timer trigger source as internal */
        | FLEXIO_TIMCTL_PINCFG(3U)          /* Timer' pin configured as output */
        | FLEXIO_TIMCTL_PINSEL(_flexio_WR)  /* Timer' pin index: WR pin */
        | FLEXIO_TIMCTL_PINPOL * (1U)       /* Timer' pin active low */
        | FLEXIO_TIMCTL_TIMOD(1U);          /* Timer mode 8-bit baud counter */

    /*
      Serial.printf("CCM_CDCDR: %x\n", CCM_CDCDR);
      Serial.printf("VERID:%x PARAM:%x CTRL:%x PIN: %x\n", IMXRT_FLEXIO2_S.VERID, IMXRT_FLEXIO2_S.PARAM, IMXRT_FLEXIO2_S.CTRL, IMXRT_FLEXIO2_S.PIN);
      Serial.printf("SHIFTSTAT:%x SHIFTERR=%x TIMSTAT=%x\n", IMXRT_FLEXIO2_S.SHIFTSTAT, IMXRT_FLEXIO2_S.SHIFTERR, IMXRT_FLEXIO2_S.TIMSTAT);
      Serial.printf("SHIFTSIEN:%x SHIFTEIEN=%x TIMIEN=%x\n", IMXRT_FLEXIO2_S.SHIFTSIEN, IMXRT_FLEXIO2_S.SHIFTEIEN, IMXRT_FLEXIO2_S.TIMIEN);
      Serial.printf("SHIFTSDEN:%x SHIFTSTATE=%x\n", IMXRT_FLEXIO2_S.SHIFTSDEN, IMXRT_FLEXIO2_S.SHIFTSTATE);
      for(int i=0; i<SHIFTNUM; i++){
        Serial.printf("SHIFTCTL[%d]:%x \n", i, IMXRT_FLEXIO2_S.SHIFTCTL[i]);
        }

      for(int i=0; i<SHIFTNUM; i++){
        Serial.printf("SHIFTCFG[%d]:%x \n", i, IMXRT_FLEXIO2_S.SHIFTCFG[i]);
        }

      Serial.printf("TIMCTL:%x %x %x %x\n", IMXRT_FLEXIO2_S.TIMCTL[0], IMXRT_FLEXIO2_S.TIMCTL[1], IMXRT_FLEXIO2_S.TIMCTL[2], IMXRT_FLEXIO2_S.TIMCTL[3]);
      Serial.printf("TIMCFG:%x %x %x %x\n", IMXRT_FLEXIO2_S.TIMCFG[0], IMXRT_FLEXIO2_S.TIMCFG[1], IMXRT_FLEXIO2_S.TIMCFG[2], IMXRT_FLEXIO2_S.TIMCFG[3]);
      Serial.printf("TIMCMP:%x %x %x %x\n", IMXRT_FLEXIO2_S.TIMCMP[0], IMXRT_FLEXIO2_S.TIMCMP[1], IMXRT_FLEXIO2_S.TIMCMP[2], IMXRT_FLEXIO2_S.TIMCMP[3]);
    */
    /* Enable FlexIO */
    p->CTRL |= FLEXIO_CTRL_FLEXEN;
    p->SHIFTSDEN |= 1U << (SHIFTER_DMA_REQUEST); // enable DMA trigger when shifter status flag is set on shifter SHIFTER_DMA_REQUEST
}

FASTRUN void ILI948x_t4_mm::SglBeatWR_nPrm_8(uint32_t const cmd, const uint8_t *value = NULL, uint32_t const length = 0) {
    while (WR_DMATransferDone == false) {
        // Wait for any DMA transfers to complete
    }

    FlexIO_Config_SnglBeat();
    uint32_t i;
    /* Assert CS, RS pins */

    // delay(1);
    CSLow();
    DCLow();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = cmd;

    /*Wait for transfer to be completed */
    while (0 == (p->SHIFTSTAT & _write_shifter_mask)) {
    }
    while (0 == (p->TIMSTAT & _flexio_timer_mask)) {
    }

    /* De-assert RS pin */

    microSecondDelay();
    DCHigh();
    microSecondDelay();

    if (length) {
        for (i = 0; i < length; i++) {
            p->SHIFTBUF[_write_shifter] = *value++;
            while (0 == (p->SHIFTSTAT & _write_shifter_mask)) {
            }
        }
        while (0 == (p->TIMSTAT & _flexio_timer_mask)) {
        }
    }
    microSecondDelay();
    CSHigh();
    /* De-assert CS pin */
}

FASTRUN void ILI948x_t4_mm::SglBeatWR_nPrm_16(uint32_t const cmd, const uint16_t *value, uint32_t const length) {
    while (WR_DMATransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    FlexIO_Config_SnglBeat();
    uint16_t buf;
    /* Assert CS, RS pins */
    CSLow();
    DCLow();
    // microSecondDelay();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = cmd;

    /*Wait for transfer to be completed */
    while (0 == (p->TIMSTAT & _flexio_timer_mask)) {
    }
    microSecondDelay();
    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();

    if (length) {
        for (uint32_t i = 0; i < length - 1U; i++) {
            buf = *value++;
            while (0 == (p->SHIFTSTAT & (1U << 0))) {
            }
            p->SHIFTBUF[_write_shifter] = buf >> 8;

            while (0 == (p->SHIFTSTAT & (1U << 0))) {
            }
            p->SHIFTBUF[_write_shifter] = buf & 0xFF;
        }
        buf = *value++;
        /* Write the last byte */
        while (0 == (p->SHIFTSTAT & (1U << 0))) {
        }
        p->SHIFTBUF[_write_shifter] = buf >> 8;

        while (0 == (p->SHIFTSTAT & (1U << 0))) {
        }
        p->TIMSTAT |= (1U << 0);

        p->SHIFTBUF[_write_shifter] = buf & 0xFF;

        /*Wait for transfer to be completed */
        while (0 == (p->TIMSTAT |= (1U << 0))) {
        }
    }
    microSecondDelay();
    CSHigh();
}

ILI948x_t4_mm *ILI948x_t4_mm::dmaCallback = nullptr;
DMAChannel ILI948x_t4_mm::flexDma;

FASTRUN void ILI948x_t4_mm::MulBeatWR_nPrm_DMA(uint32_t const cmd, const void *value, uint32_t const length) {
    while (WR_DMATransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    uint32_t BeatsPerMinLoop = SHIFTNUM * sizeof(uint32_t) / sizeof(uint8_t); // Number of shifters * number of 8 bit values per shifter
    uint32_t majorLoopCount, minorLoopBytes;
    uint32_t destinationModulo = 31 - (__builtin_clz(SHIFTNUM * sizeof(uint32_t))); // defines address range for circular DMA destination buffer

    FlexIO_Config_SnglBeat();
    CSLow();
    DCLow();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = cmd;

    /*Wait for transfer to be completed */

    while (0 == (p->TIMSTAT & _flexio_timer_mask)) {
    }
    microSecondDelay();
    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();

    if (length < 8) {
        // Serial.println ("In DMA but to Short to multibeat");
        const uint16_t *newValue = (uint16_t *)value;
        uint16_t buf;
        for (uint32_t i = 0; i < length; i++) {
            buf = *newValue++;
            while (0 == (p->SHIFTSTAT & (1U << 0))) {
            }
            p->SHIFTBUF[_write_shifter] = buf >> 8;

            while (0 == (p->SHIFTSTAT & (1U << 0))) {
            }
            p->SHIFTBUF[_write_shifter] = buf & 0xFF;
        }
        // Wait for transfer to be completed
        while (0 == (p->TIMSTAT & (1U << 0))) {
        }

        microSecondDelay();
        CSHigh();

    }

    else {
        // memcpy(framebuff, value, length);
        // arm_dcache_flush((void*)framebuff, sizeof(framebuff)); // always flush cache after writing to DMAMEM variable that will be accessed by DMA

        FlexIO_Config_MultiBeat();

        MulBeatCountRemain = length % BeatsPerMinLoop;
        MulBeatDataRemain = (uint16_t *)value + ((length - MulBeatCountRemain)); // pointer to the next unused byte (overflow if MulBeatCountRemain = 0)
        TotalSize = (length - MulBeatCountRemain) * 2;                           /* in bytes */
        minorLoopBytes = SHIFTNUM * sizeof(uint32_t);
        majorLoopCount = TotalSize / minorLoopBytes;
        // Serial.printf("Length(16bit): %d, Count remain(16bit): %d, Data remain: %d, TotalSize(8bit): %d, majorLoopCount: %d \n",length, MulBeatCountRemain, MulBeatDataRemain, TotalSize, majorLoopCount );

        /* Configure FlexIO with multi-beat write configuration */
        flexDma.begin();

        /* Setup DMA transfer with on-the-fly swapping of MSB and LSB in 16-bit data:
         *  Within each minor loop, read 16-bit values from buf in reverse order, then write 32bit values to SHIFTBUFBYS[i] in reverse order.
         *  Result is that every pair of bytes are swapped, while half-words are unswapped.
         *  After each minor loop, advance source address using minor loop offset. */
        int destinationAddressOffset, destinationAddressLastOffset, sourceAddressOffset, sourceAddressLastOffset, minorLoopOffset;
        volatile void *destinationAddress, *sourceAddress;

        DMA_CR |= DMA_CR_EMLM; // enable minor loop mapping

        sourceAddress = (uint16_t *)value + minorLoopBytes / sizeof(uint16_t) - 1; // last 16bit address within current minor loop
        sourceAddressOffset = -sizeof(uint16_t);                                   // read values in reverse order
        minorLoopOffset = 2 * minorLoopBytes;                                      // source address offset at end of minor loop to advance to next minor loop
        sourceAddressLastOffset = minorLoopOffset - TotalSize;                     // source address offset at completion to reset to beginning
        destinationAddress = (uint32_t *)&p->SHIFTBUFBYS[SHIFTNUM - 1];            // last 32bit shifter address (with reverse byte order)
        destinationAddressOffset = -sizeof(uint32_t);                              // write words in reverse order
        destinationAddressLastOffset = 0;

        flexDma.TCD->SADDR = sourceAddress;
        flexDma.TCD->SOFF = sourceAddressOffset;
        flexDma.TCD->SLAST = sourceAddressLastOffset;
        flexDma.TCD->DADDR = destinationAddress;
        flexDma.TCD->DOFF = destinationAddressOffset;
        flexDma.TCD->DLASTSGA = destinationAddressLastOffset;
        flexDma.TCD->ATTR =
            DMA_TCD_ATTR_SMOD(0U) | DMA_TCD_ATTR_SSIZE(DMA_TCD_ATTR_SIZE_16BIT)                   // 16bit reads
            | DMA_TCD_ATTR_DMOD(destinationModulo) | DMA_TCD_ATTR_DSIZE(DMA_TCD_ATTR_SIZE_32BIT); // 32bit writes
        flexDma.TCD->NBYTES_MLOFFYES =
            DMA_TCD_NBYTES_SMLOE | DMA_TCD_NBYTES_MLOFFYES_MLOFF(minorLoopOffset) | DMA_TCD_NBYTES_MLOFFYES_NBYTES(minorLoopBytes);
        flexDma.TCD->CITER = majorLoopCount; // Current major iteration count
        flexDma.TCD->BITER = majorLoopCount; // Starting major iteration count

        flexDma.triggerAtHardwareEvent(hw->shifters_dma_channel[SHIFTER_DMA_REQUEST]);
        flexDma.disableOnCompletion();
        flexDma.interruptAtCompletion();
        flexDma.clearComplete();

        // Serial.println("Dma setup done");

        /* Start data transfer by using DMA */
        WR_DMATransferDone = false;
        flexDma.attachInterrupt(dmaISR);
        flexDma.enable();
        // Serial.println("Starting transfer");
        dmaCallback = this;
    }
}

FASTRUN void ILI948x_t4_mm::_onCompleteCB() {
    if (_callback) {
        _callback();
    }
    return;
}

FASTRUN void ILI948x_t4_mm::dmaISR() {
    flexDma.clearInterrupt();
    asm volatile("dsb"); // prevent interrupt from re-entering
    dmaCallback->flexDma_Callback();
}

FASTRUN void ILI948x_t4_mm::flexDma_Callback() {
    // Serial.printf("DMA callback start triggred \n");

    /* the interrupt is called when the final DMA transfer completes writing to the shifter buffers, which would generally happen while
    data is still in the process of being shifted out from the second-to-last major iteration. In this state, all the status flags are cleared.
    when the second-to-last major iteration is fully shifted out, the final data is transfered from the buffers into the shifters which sets all the status flags.
    if you have only one major iteration, the status flags will be immediately set before the interrupt is called, so the while loop will be skipped. */
    while (0 == (p->SHIFTSTAT & (1U << (SHIFTNUM - 1)))) {
    }

    /* Wait the last multi-beat transfer to be completed. Clear the timer flag
    before the completing of the last beat. The last beat may has been completed
    at this point, then code would be dead in the while() below. So mask the
    while() statement and use the software delay .*/
    p->TIMSTAT |= (1U << 0U);

    /* Wait timer flag to be set to ensure the completing of the last beat.
    while(0 == (p->TIMSTAT & (1U << 0U)))
    {
    }
    */
    delayMicroseconds(200);

    if (MulBeatCountRemain) {
        // Serial.printf("MulBeatCountRemain in DMA callback: %d, MulBeatDataRemain %x \n", MulBeatCountRemain,MulBeatDataRemain);
        uint16_t value;
        /* Configure FlexIO with 1-beat write configuration */
        FlexIO_Config_SnglBeat();

        // Serial.printf("Starting single beat completion: %d \n", MulBeatCountRemain);

        /* Use polling method for data transfer */
        for (uint32_t i = 0; i < (MulBeatCountRemain); i++) {
            value = *MulBeatDataRemain++;
            while (0 == (p->SHIFTSTAT & (1U << 0))) {
            }
            p->SHIFTBUF[_write_shifter] = value >> 8;

            while (0 == (p->SHIFTSTAT & (1U << 0))) {
            }
            p->SHIFTBUF[_write_shifter] = value & 0xFF;
        }
        p->TIMSTAT |= (1U << 0);
        /*
        value = *MulBeatDataRemain++;
        //Write the last byte

        while(0 == (p->SHIFTSTAT & (1U << 0)))
            {
            }
        p->SHIFTBUF[_write_shifter] = value >> 8;

        while(0 == (p->SHIFTSTAT & (1U << 0)))
        {
        }
        p->TIMSTAT |= (1U << 0);

        p->SHIFTBUF[_write_shifter] = value & 0xFF;
        */
        /*Wait for transfer to be completed */
        while (0 == (p->TIMSTAT |= (1U << 0))) {
        }
        // Serial.println("Finished single beat completion");
    }

    microSecondDelay();
    CSHigh();
    /* the for loop is probably not sufficient to complete the transfer. Shifting out all 32 bytes takes (32 beats)/(6 MHz) = 5.333 microseconds which is over 3000 CPU cycles.
    If you really need to wait in this callback until all the data has been shifted out, the while loop is probably the correct solution and I don't think it risks an infinite loop.
    however, it seems like a waste of time to wait here, since the process otherwise completes in the background and the shifter buffers are ready to receive new data while the transfer completes.
    I think in most applications you could continue without waiting. You can start a new DMA transfer as soon as the first one completes (no need to wait for FlexIO to finish shifting). */

    WR_DMATransferDone = true;
    //    flexDma.disable(); // not necessary because flexDma is already configured to disable on completion
    if (isCB) {
        // Serial.printf("custom callback triggred \n");
        _onCompleteCB();
    }
    // Serial.printf("DMA callback end triggred \n");
}

void ILI948x_t4_mm::DMAerror() {
    if (flexDma.error()) {
        Serial.print("DMA error: ");
        Serial.println(DMA_ES, HEX);
    }
}

void ILI948x_t4_mm::beginWrite16BitColors() {
    while (WR_DMATransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    FlexIO_Config_SnglBeat();
    /* Assert CS, RS pins */
    CSLow();
    DCLow();
    // microSecondDelay();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = ILI9488_RAMWR;

    /*Wait for transfer to be completed */
    while (0 == (p->TIMSTAT & _flexio_timer_mask)) {
    }
    microSecondDelay();
    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();
}

void ILI948x_t4_mm::write16BitColor(uint16_t color) {
    while (0 == (p->SHIFTSTAT & (1U << 0))) {
    }
    p->SHIFTBUF[_write_shifter] = color >> 8;

    while (0 == (p->SHIFTSTAT & (1U << 0))) {
    }
    p->SHIFTBUF[_write_shifter] = color & 0xFF;
}

void ILI948x_t4_mm::endWrite16BitColors() {
    /*Wait for transfer to be completed */
    while (0 == (p->TIMSTAT |= (1U << 0))) {
    }
    microSecondDelay();
    CSHigh();
}

FASTRUN void ILI948x_t4_mm::write16BitColor(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, const uint16_t *pcolors, uint16_t count) {
    while (WR_DMATransferDone == false) {
        // Wait for any DMA transfers to complete
    }
    // uint32_t area = (x2-x1+1)*(y2-y1+1);
    uint32_t area = count;
    // if (!((_lastx1 == x1) && (_lastx2 == x2) && (_lasty1 == y1) && (_lasty2 == y2))) {
    //   setAddrWindow( x1, y1, x2, y2);
    //    _lastx1 = x1;  _lastx2 = x2;  _lasty1 = y1;  _lasty2 = y2;
    // }
    setAddr(x1, y1, x2, y2);
    SglBeatWR_nPrm_16(ILI9488_RAMWR, pcolors, area);
}

uint16_t ILI948x_t4_mm::readPixel(int16_t x, int16_t y) {
    uint16_t color;
    readRect(x, y, 1, 1, &color);
    return color;
}

void ILI948x_t4_mm::readRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t *pcolors) {
    // Serial.printf("readRect(%d, %d, %d, %d, %p)\n", x, y, w, h, pcolors);
    //  first do any clipping.
    if ((x >= _displayclipx2) || (y >= _displayclipy2))
        return;
    if (((x + w) <= _displayclipx1) || ((y + h) <= _displayclipy1))
        return;
    if (x < _displayclipx1) {
        w -= (_displayclipx1 - x);
        x = _displayclipx1;
    }
    if (y < _displayclipy1) {
        h -= (_displayclipy1 - y);
        y = _displayclipy1;
    }
    if ((x + w - 1) >= _displayclipx2)
        w = _displayclipx2 - x;
    if ((y + h - 1) >= _displayclipy2)
        h = _displayclipy2 - y;

    // We probably need to set the rectangle
    setAddr(x, y, x + w - 1, y + h - 1);
    // now set to ramRD command
    FlexIO_Config_SnglBeat();
    /* Assert CS, RS pins */
    CSLow();
    DCLow();
    // microSecondDelay();

    /* Write command index */
    p->SHIFTBUF[_write_shifter] = ILI9488_RAMRD;

    /*Wait for transfer to be completed */
    while (0 == (p->TIMSTAT & _flexio_timer_mask)) {
    }
    microSecondDelay();

    /* De-assert RS pin */
    DCHigh();
    microSecondDelay();
    // delayMicroseconds(50);

    FlexIO_Clear_Config_SnglBeat();
    FlexIO_Config_SnglBeat_Read();

    uint8_t dummy = 0;
#define DUMMY_COUNT 1
    for (uint8_t i = 0; i < DUMMY_COUNT; i++) {
        // read in dummy bytes
        while (0 == (p->SHIFTSTAT & _read_shifter_mask)) {
        }
        dummy = p->SHIFTBUFBYS[_read_shifter];
        // Serial.printf("\tD%u=%x\n", i, dummy);
    }
    /*Wait for transfer to be completed */
    if (_display_name != ILI9488) {
        // 16 bit mode
        int count_pixels = w * h;
        uint8_t *pc = (uint8_t *)pcolors;
        while (count_pixels--) {
            while (0 == (p->SHIFTSTAT & (1U << 3))) {
            }
            uint8_t b1 = (p->SHIFTBUFBYS[_read_shifter] & 0xff);

            while (0 == (p->SHIFTSTAT & (1U << 3))) {
            }
            *pc++ = (p->SHIFTBUFBYS[_read_shifter] & 0xff);
            *pc++ = b1;
        }
    } else {
        int count_pixels = w * h;
        while (count_pixels--) {
            uint8_t r, g, b;
            while (0 == (p->SHIFTSTAT & (1U << 3))) {
            }
            r = (p->SHIFTBUFBYS[_read_shifter] & 0xff);

            while (0 == (p->SHIFTSTAT & (1U << 3))) {
            }
            g = (p->SHIFTBUFBYS[_read_shifter] & 0xff);

            while (0 == (p->SHIFTSTAT & (1U << 3))) {
            }
            b = (p->SHIFTBUFBYS[_read_shifter] & 0xff);

            *pcolors++ = color565(r, g, b);
        }
    }

    // Set FlexIO back to Write mode
    FlexIO_Config_SnglBeat();
}
