// Motor.h
#ifndef BOT_H
#define BOT_H

#include <Arduino.h>
#include "Motor.h"
#include "Power.h"

//Overall Class for the Bot
class Bot {
  private:
    //Create two motors, left and right motors
    Motor left;
    Motor right;

    
    //for displaying the power 
    int powerGreen;
    int powerYellow;
    int powerRed;

  public:
    //Set up the Bot
    Bot(int M11, int M12, float ratio1, int M21, int M22, float ratio2, int PArdu, int PBread);
    Bot_set(int powerGreen, int powerYellow, int powerRed);
    //Motor Stuff
    forward(int speed);
    reverse(int speed);
    pivotRight(int angle);
    pivotLeft(int angle);
    turnRight();
    turnLeft();

    //Power Stuff
    //Bot.system.readPower() to read voltages of arduinos with Bot.system.voltArdu 
    //and Bot.system.voltBread for voltages of 9V and 6V respectively on a range scale 0 - 5
    Power system;
    displayVolt();
};

#endif