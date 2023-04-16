#include "Bot.h"

Bot::Bot(int M11, int M12, float ratio1,
        int M21, int M22, float ratio2)
{
motor_left.Motor_set(M11,M12,ratio1);
motor_right.Motor_set(M21,M22,ratio2);
}


Bot::forward(int speed)
{
  motor_left.drive(speed,0);
  motor_right.drive(speed,1);

}

Bot::reverse(int speed){
  motor_left.drive(speed,1);
  motor_right.drive(speed,0);
}

Bot::pivotRight(int angle)
{
  int speed = 100;
  float radius = 5.25/2;
  float RadAngle = angle*2*PI/180;

  float time = 1000*(5/5.39)*(1/7.42)*RadAngle*radius;
  motor_left.drive(speed,0);
  motor_right.drive(speed,0);
  delay(time);
}

Bot::pivotLeft(int angle)
{
  int speed = 100;
  float radius = 5.25/2;
  float RadAngle = angle*2*PI/180;

  float time = 1000*(5/5.39)*(1/7.42)*RadAngle*radius;
  motor_left.drive(speed,1);
  motor_right.drive(speed,1);
  delay(time);
}

Bot::turnRight()
{
  motor_left.drive(50,0);
  motor_right.drive(100,1);
  delay(2000);
  motor_left.drive(0,0);
  motor_right.drive(0,1);
}

Bot::turnLeft()
{
  motor_left.drive(100,0);
  motor_right.drive(50,1);
  delay(2000);
  motor_left.drive(0,0);
  motor_right.drive(0,1);
}
