// ======================================
// Filename:
//   config.h
//
// Product or product-subsystem:
//   application
//
// Description:
//   global configuration.
// ======================================

#ifndef BIRDO_CONFIG_H
#define BIRDO_CONFIG_H

#include <Arduino.h>
#include "BDStepper.h"

// ============= User configuration ======================= may touch

#define STATE_INIT_TIMER 5000       // in Miliseconds
#define STATE_IDLE_TIMER 30000      // in Miliseconds
#define STATE_MESSAGE_TIMER 5000    // in Miliseconds
#define STATE_WELL_DONE_TIMER 5000  // in Miliseconds

#define BASE_BREATHE_TIME 1000      // in Miliseconds
#define BASE_LONG_PRESS_TIME 1000   // in Miliseconds

#define VOLUME_LEVEL 10     // max 30
#define LDR_OFFSET 1.0f     // [0..1]

#define DEFAULT_COLOR Drivers::Color   {255, 70,  0} // orange
#define ACCENT_COLOR Drivers::Color    {  0,255,255} // cyan
#define MESSAGE_COLOR Drivers::Color   {255, 25,150} // pink
#define WELL_DONE_COLOR Drivers::Color {100,255,  0} // green

// ============= System configuration ===================== don't touch

#define ENABLE_BOT_STEPPER true
#define ENABLE_TOP_STEPPER true

#define ENABLE_NOSE_LEDS true
#define ENABLE_BASE_LEDS true

#define ENABLE_LDR true

#define ENABLE_SOUND true

#define STATE_CHECK_PRESS_TIMER 400

// ============= Mechanical configuration ================= // don't touch

#define MICROSTEPS Drivers::Microsteps_e::STEP_1_32 // defining the microsteps
#define REDUCTION 4                                 // reduction is zero (with 0, you cannot calculate)

#define MOT_0_STEP_PIN GPIO_NUM_4 // stepper driver [1] step pin
#define MOT_0_DIR_PIN GPIO_NUM_5  // stepper driver [1] direction pin
#define MOT_0_ENB_PIN GPIO_NUM_22 // stepper driver [1] enable pin

#define MOT_1_STEP_PIN GPIO_NUM_18 // stepper driver [2] step pin
#define MOT_1_DIR_PIN GPIO_NUM_19  // stepper driver [2] direction pin
#define MOT_1_ENB_PIN GPIO_NUM_23  // stepper driver [2] enable pin

#define PIXEL_PIN GPIO_NUM_14 // defining the pin of the LED strip(s)
#define NUM_PIXELS 24        // defining the amount of pixels of the LED (each strip is 8 LEDs * 3 = 24)

#define NOSE_PIXEL_PIN GPIO_NUM_27
#define NUM_NOSE_PIXELS 12

#define LDR_PIN GPIO_NUM_15  //defining the pin of the LDR sensor

#define BUTTON_PIN GPIO_NUM_13
#define LED_BUT_PIN GPIO_NUM_12
#define LED_BUT_CHANNEL 0

#define UART_TX GPIO_NUM_17
#define UART_RX GPIO_NUM_16

#endif // BIRDO_CONFIG_H