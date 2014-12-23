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

#ifndef a4988_h
#define a4988_h

class a4988 {
  public:
    // constructors:
    a4988(int motor_steps, int ms1_pin, int ms2_pin, int ms3_pin, int dir_pin, int enable_pin, int step_pin);

    // speed setter method:
    void setDelay(unsigned long delay);   // in microseconds

    void enable(int enable);

    // mover method:
    void setDirection(int direction);     // 0 forward, 1 backward
    void step(unsigned long num_steps);   // step a given number of steps
    void stepOnce(void);
    void setStepMode(int stepMode);       // (1 /) 1, 2, 4, 8, or 16 

  private:
    void stepMotor(int this_step);

    
    int direction;               // Direction of rotation
    int motor_steps;             // number of steps motor has per revolution
    unsigned long step_delay;    // delay between steps, in us
    int num_steps;               // total number of steps to step
    int step_number;             // which step the motor is on
    int step_mode;               // which mode 1 / 1, 2, 4, 8, or 16
    int step_pin;                // pin which controls stepping

    // control pin numbers:
    int ms1_pin;                 // for setting different microstepping modes
    int ms2_pin;                 // for setting different microstepping modes
    int ms3_pin;                 // for setting different microstepping modes
    int dir_pin;
    int enable_pin;
    
};

#endif //a4988_h
