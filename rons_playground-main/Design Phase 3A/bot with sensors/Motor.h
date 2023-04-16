// Motor.h
#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  private:
    int PinA;
    int PinB;
    float ratio;


  public:
    Motor();
    Motor_set(int pin1, int pin2, float ratio);
    drive(int speed, bool dir);
};

#endif