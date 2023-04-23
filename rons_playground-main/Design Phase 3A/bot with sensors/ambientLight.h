#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include <Arduino.h>

class ambientLight {
  private:

    int sensor_pin;
    int led_pin;

    long counter_period;
    void blink(bool isday, int counter);


  public:
    ambientLight(int sensor, int led, int delay);
    //counter_period gets times somthing to scale to half a sec 
    int DetectLight(int counter);




};

#endif