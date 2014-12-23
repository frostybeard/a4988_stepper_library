a4988 stepper library for Arduino
=======================

A stepper library for Arduino for Allegro a4988 microstepper boards.

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

## constructor for set up

a4988(int motor_steps, int ms1_pin, int ms2_pin, int ms3_pin, int dir_pin, int enable_pin, int step_pin);

## delay setter method:

void setDelay(unsigned long delay); 
- delay between steps, in microseconds

## microstepping control

void setStepMode(int stepMode);
- ( 1 / ) 1, 2, 4, 8, or 16 
- sets full, half, quarter, 1/8, and 1/ 16 step microstepping modes

## set direction

void setDirection(int direction);
- 0 or 1 to change direction of stepping
- the datasheet did not specify which was forward and which was backward


## stepping methods

void step(unsigned long num_steps);
- step a given number of steps

void stepOnce(void);
- step one step

## shut down motor:

void enable(int enable);
- 0 enable, 1 disable
- stops current from flowing through the motor
- can save energy and help keep things cool
- startup can be jumpy, though


