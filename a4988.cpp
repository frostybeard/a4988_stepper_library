/*
  a4988.cpp - - Arduino library for using the a4988 stepper driver
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

#include "Arduino.h"
#include "a4988.h"

// constructor to set up pins and initialize data
a4988::a4988(int motor_steps, int ms1_pin, int ms2_pin, int ms3_pin, int dir_pin, int enable_pin, int step_pin)
{
   this->enable_pin = enable_pin;
   this->dir_pin = dir_pin;
   this->ms1_pin = ms1_pin;
   this->ms2_pin = ms2_pin;
   this->ms3_pin = ms3_pin;
   this->step_pin = step_pin;

   // setup the pins on the microcontroller:
   pinMode(this->ms1_pin, OUTPUT);
   pinMode(this->ms2_pin, OUTPUT);
   pinMode(this->ms3_pin, OUTPUT);
   pinMode(this->dir_pin, OUTPUT);
   pinMode(this->enable_pin, OUTPUT);
   pinMode(this->step_pin, OUTPUT);

   if(motor_steps != 0)
   {
      this->motor_steps = motor_steps; 
   }
   else
   {
      this->motor_steps = 200;       // a common value for steppers
   }

   // use setDelay to change before stepping, otherwise default
   this->step_delay = 20000;         // 20000 us (20 ms) as a default
                                     
}

void a4988::enable(int enable)
{
   digitalWrite(this->enable_pin,enable);  // set enable pin on/off
}

// set delay in microseconds, set before starting to step
void a4988::setDelay(unsigned long delay)
{
   this->step_delay = delay;
}

// set direction: 0 or 1
void a4988::setDirection(int direction)
{
   if(direction == 0)
   {
      digitalWrite(dir_pin,HIGH); 
   }
   else 
   {
      digitalWrite(dir_pin,LOW);
   }
}

// step only once
void a4988::stepOnce(void)
{
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(this->step_delay);
    digitalWrite(step_pin, LOW);
    delayMicroseconds(this->step_delay);
}

// step given number of times
void a4988::step(unsigned long num_steps)
{
   unsigned long x;
   for(x = 0; x < num_steps; x++)
   {
      this->stepOnce();
   }
}

// set microstepping mode
// (1 /) 1, 2, 4, 8, or 16
void a4988::setStepMode(int stepMode)
{   
    this->step_mode = stepMode;
    switch (stepMode)
    {
                  // MS1   MS2   MS3
      case 16:    // high  high  high
      digitalWrite(ms1_pin, HIGH);
      digitalWrite(ms2_pin, HIGH);
      digitalWrite(ms3_pin, HIGH);
      break;
      case 8:    // high  high  low
      digitalWrite(ms1_pin, HIGH);
      digitalWrite(ms2_pin, HIGH);
      digitalWrite(ms3_pin, LOW);
      break;
      case 4:    // low   high  low
      digitalWrite(ms1_pin, LOW);
      digitalWrite(ms2_pin, HIGH);
      digitalWrite(ms3_pin, LOW);
      break;
      case 2:    // high  low   low
      digitalWrite(ms1_pin, HIGH);
      digitalWrite(ms2_pin, LOW);
      digitalWrite(ms3_pin, LOW);
      break;
      case 1:    // low   low   low
      digitalWrite(ms1_pin, LOW);
      digitalWrite(ms2_pin, LOW);
      digitalWrite(ms3_pin, LOW);
      break;
    }
}





