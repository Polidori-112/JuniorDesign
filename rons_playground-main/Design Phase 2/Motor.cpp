#include "motor.h"

Motor::Motor()
{

}

Motor::Motor_set(int pin1, int pin2, float ratio)
{
  PinA = pin1;
  PinB = pin2;
  ratio = ratio;
  init();
}

Motor::init(){
  pinMode(PinA, OUTPUT);
  pinMode(PinB, OUTPUT);
}

Motor::drive(int speed, bool dir){


  if(dir){
    analogWrite(PinA,speed);//*ratio);
    digitalWrite(PinB,LOW);
  }else{
    digitalWrite(PinA,LOW);
    analogWrite(PinB,speed);//*ratio);
  }
}