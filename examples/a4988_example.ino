/*
  a4988 library - - Arduino library for using the a4988 stepper driver
  William Smith, 2014
  
  The A4988 stepper driver is for Pololu stepper driver boards
  and compatible clones. These boards use the Allegro a4988
  stepper motor driver IC. (see Allegro website for datasheet)

  This library diverges from others that are around, in that it
  assumes that the MS1, MS2, and MS3 pins are connected to gpio
  pins on the Arduino, allowing control over the microstepping
  modes.
  
  The A4988 is capable of microstepping down to 1/16 of a step,
  enabling fine control over the stepper motor. This fine control
  can be used in, among other things, 3D printers.

  This library provides an interface for setting the different
  step modes, going from full step down to 1/16 step, using a
  simple setter function, where the argument is 1,2,4,8, or 16.

  
     MS1   MS2   MS3
    -----------------
     low   low   low   Full step
     high  low   low   Half step
     low   high  low   1/4 step
     high  high  low   1/8 step
     high  high  high  1/16 step

  Note:
  Lower delay values can be used in the microstepping mode.
  Values as low as 25 usec can be used in the 1/16 mode
  with some motors. 

*/

#include <a4988.h>


#define MS1PIN 8
#define MS2PIN 9
#define MS3PIN 10
#define DIRPIN 4
#define STEPPIN 5
#define ENABLEPIN 6
#define MOTOR_STEPS 200

a4988 myA4988(MOTOR_STEPS, MS1PIN, MS2PIN, MS3PIN, DIRPIN, ENABLEPIN, STEPPIN);

void setup() {
  // put your setup code here, to run once:
  myA4988.enable(0);
  myA4988.setStepMode(16);
  myA4988.setDelay(50);
}

void loop() {
  // 1 rev. in 1/16 step mode with 50 us delay
  myA4988.setStepMode(16);
  myA4988.setDelay(50);  
  myA4988.setDirection(0);
  myA4988.step(3200);
  delay(1000);
  myA4988.setDirection(1);
  myA4988.step(3200);
  delay(1000);
  
  // 1 rev. in 1/8 step mode with 100 us delay
  myA4988.setStepMode(8);
  myA4988.setDelay(100);  
  myA4988.setDirection(0);
  myA4988.step(1600);
  delay(1000);
  myA4988.setDirection(1);
  myA4988.step(1600);
  delay(1000);
  
  // 1 rev. in 1/4 step mode with 200 us delay
  myA4988.setStepMode(4);
  myA4988.setDelay(200);  
  myA4988.setDirection(0);
  myA4988.step(800);
  delay(1000);
  myA4988.setDirection(1);
  myA4988.step(800);
  delay(1000);
  
  // 1 rev. in 1/2 step mode with 400 us delay
  myA4988.setStepMode(2);
  myA4988.setDelay(400);  
  myA4988.setDirection(0);
  myA4988.step(400);
  delay(1000);
  myA4988.setDirection(1);
  myA4988.step(400);
  delay(1000);

  // 1 rev. in full step mode with 800 us delay
  myA4988.setStepMode(1);
  myA4988.setDelay(800);  
  myA4988.setDirection(0);
  myA4988.step(200);
  delay(1000);
  myA4988.setDirection(1);
  myA4988.step(200);
  delay(1000);
}
