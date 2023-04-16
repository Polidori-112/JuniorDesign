#include "Bot.h"

Bot robo(9,10,1,5,6,1); 

void setup() {
delay(1000);
Serial.begin(9600);
}

void loop() {

  //robo.pivotRight(90);
  robo.forward(100);
  delay(2000);
  robo.forward(0);
  delay(1000);
  robo.reverse(100);
  delay(2000);
  robo.forward(0);
  delay(1000);

  // robo.pivotRight(180);
  // robo.forward(0);
  // delay(1000);

  // robo.forward(100);
  // delay(2000);
  // robo.forward(0);
  // delay(1000);
  // robo.pivotLeft(180);
  // robo.forward(0);
  // delay(1000);
  // robo.forward(100);

  // delay(2000);
  // robo.forward(0);
  // delay(1000);
  // robo.turnRight();
  // delay(1000);
  // robo.turnLeft();
  // delay(1000);
  

}
