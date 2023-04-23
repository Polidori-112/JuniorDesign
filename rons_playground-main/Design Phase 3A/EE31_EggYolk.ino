#include "Bot.h";

#define V9 A1
#define V6 A0
#define pG 11
#define pY 12
#define pR 13

//define some global variables
unsigned long startMillis;
unsigned long currMillis;
Bot robo(9,10,1,5,6,1,V9,V6); 

void setup() {
  delay(1000);
  Serial.begin(9600);

  robo.Bot_set(pG, pY, pR);

  pinMode(13,OUTPUT); //Power greenLED
  pinMode(12,OUTPUT); //Power yellowLED
  pinMode(11,OUTPUT); //Power redLED

}

//above 3 - green, above 2 - orange, below 1 - red 
void loop() {
  //int volt6V;
  //int volt9V;
  //startMillis = millis();
  //currMillis = startMillis;
  //Flash 
  //while (currMillis-startMillis <= 6000) {
  //  robo.system.readPower();
    //flash6V = robo.system.voltArdu;
    //flash9V = robo.system.voltBread;
  //  if ((currMillis - startMillis) % 50 > 50){
    
    //}
  //}
  //robo.pivotRight(90);
  robo.system.readPower();
  Serial.println(robo.system.voltArdu);
  Serial.println(robo.system.voltBread);
  Serial.println(robo.system.levelArdu);
  Serial.println(robo.system.levelBread);
  robo.displayVolt();

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
