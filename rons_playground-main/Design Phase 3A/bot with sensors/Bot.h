// Motor.h
#ifndef BOT_H
#define BOT_H

#include <Arduino.h>
#include "Motor.h"

class Bot {
  private:
    Motor motor_left;
    Motor motor_right;

  public:
    Bot(int M11, int M12, float ratio1,
        int M21, int M22, float ratio2);
    forward(int speed);
    reverse(int speed);
    pivotRight(int angle);
    pivotLeft(int angle);
    turnRight();
    turnLeft();
};

#endif