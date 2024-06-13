//=============================================================================
// Default flexio pins - Can be setup for different teensy 4.x boards
//=============================================================================

#if defined(ARDUINO_TEENSY_MICROMOD)
// FLEXIO2 pins.

#define DISPLAY_WR 10  // FLEXIO2:0
#define DISPLAY_RD 12  // FLEXIO2:1

#define DISPLAY_D0 40 // 40      B0_04   FlexIO2:4
#define DISPLAY_D1 41 // 41      B0_05   FlexIO2:5
#define DISPLAY_D2 42 // 42      B0_06   FlexIO2:6
#define DISPLAY_D3 43 // 43      B0_07   FlexIO2:7
#define DISPLAY_D4 44 // 44      B0_08   FlexIO2:8
#define DISPLAY_D5 45 // 45      B0_09   FlexIO2:9
#define DISPLAY_D6 6  // 6       B0_10   FlexIO2:10
#define DISPLAY_D7 9  // 9       B0_11   FlexIO2:11
#endif