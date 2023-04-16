#include "ambientLight.h"

ambientLight::ambientLight(int sensor, int led, int delay)
{
  sensor_pin = sensor;
  led_pin = led;
  counter_period = 1000000/delay;

  pinMode(sensor_pin, INPUT);
  pinMode(led_pin, OUTPUT);

}

int ambientLight::DetectLight(int counter)
{

  bool isday = true;
  int light = analogRead(sensor_pin);
  if(light > 125){
    isday = false;
  }
  blink(isday, counter);

}

void ambientLight::blink(bool isday, int counter) {
  /*counter increments every delay us*/

  /* we want a desired delay of 1/2 seconds */

    if(isday){
      // Serial.print(counter%counter_period);
      // Serial.print("    ");
      // Serial.println(counter_period/2);
      if ((counter%counter_period) < (counter_period/2)) {
        digitalWrite(led_pin,HIGH);
      } else {
        digitalWrite(led_pin,LOW);
      }
      
    }else{
      digitalWrite(led_pin,HIGH);
    }
  }

