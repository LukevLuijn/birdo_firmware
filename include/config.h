
#ifndef BIRDO_CONFIG_H
#define BIRDO_CONFIG_H

#include <Arduino.h>

#include "BStepper.h"

#define MICROSTEPS Drivers::Microsteps_e::STEP_1_2 // defining the microsteps
#define REDUCTION 1                              // reduction is zero (with 0, you cannot calculate)

#define MOT_0_STEP_PIN GPIO_NUM_4 // stepper driver [1] step pin
#define MOT_0_DIR_PIN GPIO_NUM_5  // stepper driver [1] direction pin
#define MOT_0_ENB_PIN GPIO_NUM_22 // stepper driver [1] enable pin

#define MOT_1_STEP_PIN GPIO_NUM_18 // stepper driver [2] step pin
#define MOT_1_DIR_PIN GPIO_NUM_19  // stepper driver [2] direction pin
#define MOT_1_ENB_PIN GPIO_NUM_23  // stepper driver [2] enable pin

#define PIXEL_PIN GPIO_NUM_4 // defining the pin of the LED strip(s)
#define NUM_PIXELS 24        // defining the amount of pixels of the LED (each strip is 8 LEDs * 3 = 24)
#define LDR_PIN GPIO_NUM_15  //defining the pin of the LDR sensor

#define BUTTON_PIN GPIO_NUM_23
#define LED_BUT_PIN GPIO_NUM_5
#define LED_BUT_CHANNEL 0

#endif // BIRDO_CONFIG_H