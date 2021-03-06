// Hardware-specific header file to use the SmartLED Shield V4 with the OSHPark Adapter for Teensy 4:
// https://oshpark.com/shared_projects/yVCGECuY
//    Only Teensy 4.0/4.1 models are supported.
//    Only SmartLED Shield V4 (for Teensy 3) is supported.
//    APA LED driving is not tested yet but the hardware is designed to make this possible in the future.
// No jumper wires or other modifications are needed with the OSHPark Adapter.
//
// Some of the pin assignments can be changed using solderable jumpers on the adapter board:
// JP1 & JP4:
//    Default: Pin 8 connected to BUFFER_CLK, Pin 7 free
//    Alt: Pin 7 connected to BUFFER_CLK, Pin 8 free
//      To use the alternate clock pin, in addition to soldering the jumpers you must set flag SMARTMATRIX_OPTIONS_T4_CLK_PIN_ALT in kMatrixOptions
// JP2 & JP3:
//    Default: Pin 4 connected to SPI_SCK, Pin 5 connected to SPI_MOSI (intended for APA102 driving via SPI emulation), LED Matrix is drivable at the same time
//    Alt: Pins 4 & 5 NC, Pin 13 connected to SPI_SCK, Pin 11 connected to SPI_MOSI (intended for APA103 driving via hardware SPI), LED Matrix not drivable at the same time
// The following unused Teensy 4 pins are made available on the shield but some are in different positions marked on the OSHPark Adapter:
//    Teensy 4 pins free:   0, 1, 7/8, 14, 15, 16, 17, 18, 19, 20, 21, 23
//    Locations on shield:  0, 1,   9, 10, 15, 16, 11, 18, 19, 12, 22, 23
  
// Note: only one MatrixHardware_*.h file should be included per project

#ifndef MATRIX_HARDWARE_H
#define MATRIX_HARDWARE_H

/* an advanced user may need to tweak these values */

// size of latch pulse - can be short for V4 shield which doesn't need to update ADDX lines during latch pulse
// 20 is minimum working value on DP5020B panel
// set to 100 for improved support with FM6126A panel 
// don't exceed 150 to avoid interference between latch and data transfer
#define LATCH_TIMER_PULSE_WIDTH_NS 100  

// max delay from rising edge of latch pulse to falling edge of first pixel clock
// increase this value if DMA use is delaying clock
// Measured 220 ns delay at 600 MHz clock speed, 160 ns at 816 MHz. Slower speeds are not supported.
// Using larger delay for safety.
#define LATCH_TO_CLK_DELAY_NS 400

// Pixel clock frequency is generated using the 480 MHz PLL3 clock and a divide-by-n counter. Frequency is independent of CPU clock speed.
// Must increment divider value by 2 (division ratio is always even)
// Minimum tested working value is 20 (corresponding to 24 MHz clock frequency) due to panel hardware limitations on the panels tested
// Using value of 24 (corresponding to 20 MHz clock frequency) because it seems to improve intermittent glitching issue
// Larger values may be more stable, but will decrease maximum refresh rate
#define FLEXIO_CLOCK_DIVIDER 24

// Amount of time required to transfer 32 pixels
// Adding 50 ns overhead time to improve stability
#define PANEL_32_PIXELDATA_TRANSFER_MAXIMUM_NS  ((32*FLEXIO_CLOCK_DIVIDER*1000/480) + 50)

/* this section describes how the microcontroller is attached to the display */

// active pin number definitions
#define FLEXPWM_PIN_OE_TEENSY_PIN       2
#define FLEXPWM_PIN_LATCH_TEENSY_PIN    3
#define FLEXIO_PIN_CLK_TEENSY_PIN       8
#define FLEXIO_PIN_CLK_TEENSY_PIN_ALT   7
#define FLEXIO_PIN_B0_TEENSY_PIN        10
#define FLEXIO_PIN_R0_TEENSY_PIN        6
#define FLEXIO_PIN_R1_TEENSY_PIN        12
#define FLEXIO_PIN_G0_TEENSY_PIN        9
#define FLEXIO_PIN_G1_TEENSY_PIN        11
#define FLEXIO_PIN_B1_TEENSY_PIN        13

// note: data bit order is calculated in setup using the pin number definitions

#endif
