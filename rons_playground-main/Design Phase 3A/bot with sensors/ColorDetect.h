#ifndef COLORDETECT_H
#define COLORDETECT_H

#include <Arduino.h>

class ColorDetect {
  private:

    int sensor_pin;
    int color;


  public:
    ColorDetect(int sensor);
    int DetectColor();


};

#endif

