// Power.h
#ifndef POWER_H
#define POWER_H

#include <Arduino.h>

class Power {
  private:
    int pinArdu;
    int pinBread;
    init();

  public:
    float voltArdu;
    float voltBread;
    int levelArdu;
    int levelBread;
    Power();
    readPower();
    Power_set(int pin1, int pin2);
    //drive(int speed, bool dir);
};

#endif