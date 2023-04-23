#include "Bot.h"

Bot::Bot(int M11, int M12, float ratio1,
        int M21, int M22, float ratio2, int PArdu, int PBread)
{
left.Motor_set(M11,M12,ratio1);
right.Motor_set(M21,M22,ratio2);
system.Power_set(PA, PB);
}

Bot::Bot_set(int pin1, int pin2, int pin3) {
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  powerGreen = pin1;
  powerYellow = pin2;
  powerRed = pin3;

}

Bot::forward(int speed)
{
  left.drive(speed,0);
  right.drive(speed,1);
}

Bot::reverse(int speed){
  left.drive(speed,1);
  right.drive(speed,0);
}

Bot::pivotRight(int angle)
{
  int speed = 100;
  float radius = 5.25/2;
  float RadAngle = angle*2*PI/180;

  float time = 1000*(5/5.39)*(1/7.42)*RadAngle*radius;
  left.drive(speed,0);
  right.drive(speed,0);
  delay(time);
}

Bot::pivotLeft(int angle)
{
  int speed = 100;
  float radius = 5.25/2;
  float RadAngle = angle*2*PI/180;

  float time = 1000*(5/5.39)*(1/7.42)*RadAngle*radius;
  left.drive(speed,1);
  right.drive(speed,1);
  delay(time);
}

Bot::turnRight()
{
  left.drive(50,0);
  right.drive(100,1);
  delay(2000);
  left.drive(0,0);
  right.drive(0,1);
}

Bot::turnLeft()
{
  left.drive(100,0);
  right.drive(50,1);
  delay(2000);
  left.drive(0,0);
  right.drive(0,1);
}

//in progress
Bot::displayVolt() {
  system.readPower();
  if (system.levelArdu == 2 and system.levelBread == 2) {
    analogWrite(powerGreen,200);
    analogWrite(powerYellow,0);
    analogWrite(powerRed,0);
  } else if (system.levelArdu == 1 and system.levelBread == 2 or 
             system.levelArdu == 2 and system.levelBread == 1) {
    analogWrite(powerGreen,200);
    analogWrite(powerYellow,200);
    analogWrite(powerRed,0);
  } else if (system.levelArdu == 0 and system.levelBread == 2 or 
             system.levelArdu == 2 and system.levelBread == 0) {
    analogWrite(powerGreen,200);
    analogWrite(powerYellow,0);
    analogWrite(powerRed,200);
  } else if (system.levelArdu == 0 and system.levelBread == 1 or 
             system.levelArdu == 1 and system.levelBread == 0) {
    analogWrite(powerGreen,0);
    analogWrite(powerYellow,200);
    analogWrite(powerRed,200);
  } else {
    analogWrite(powerGreen,0);
    analogWrite(powerYellow,0);
    analogWrite(powerRed,200);
  }
  int ardu = system.voltArdu;
  int bread = system.voltBread;
}
