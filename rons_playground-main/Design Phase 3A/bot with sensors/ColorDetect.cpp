#include "ColorDetect.h"

  /*
   * 0 = black
   * 1 = red
   * 2 = blue
   * 3 = yellow
   */

ColorDetect::ColorDetect(int sensor) {
  sensor_pin = sensor;

  pinMode(sensor_pin, INPUT);

  color = 0;


}

int ColorDetect::DetectColor() {

  color = analogRead(sensor_pin);
  //Serial.println(color);
  if (color > 823) { //black = 827
    //Serial.println("black");
    color = 0;
  } else if (color < 806){ //yellow = 800
    //Serial.println("yellow");
    color = 3;
  }else if(color > 815) {
    //Serial.println("blue"); //blue = 819
    color = 2;
  } else {
    //Serial.println("red");//red = 812
    color = 1;
  }

  return color;

}


