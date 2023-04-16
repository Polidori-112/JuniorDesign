#include "bot.h"
#include "ColorDetect.h"
#include "ambientLight.h"
#include "Bot.h"


#define TimeDelay 1 //time delay in ms
#define period 20 //needs to be a factor of all the modulos we are using for perfect use;

//color detection pins
#define color_pin A5

//ambient light pins
#define light_pin A0
#define ambientLed 8

//motor pins
#define M11 9
#define M12 10
#define M21 5
#define M22 6

//Create modules for each of the modules and subcomponents
ColorDetect   left(color_pin);
ambientLight  lightDetect(light_pin, ambientLed, TimeDelay);
Bot           robo(M11, M12, 1, M21, M22, 1);

//initialize color values
int color=0;

  
//initialize timer values
long prev_time = 0;
long cur_time = 0;
long counter = 0;


void setup() {
  Serial.begin(9600);

  //initalize timer
  cur_time = micros();
}

void loop() {
    prev_time = cur_time;

    /******** do other bot operations **************/



    //call color detectors
    color = left.DetectColor();

    // if (color == 0) {
    //   Serial.println("black");
    // } else if (color == 1) {
    //   Serial.println("red");
    // } else if (color == 2) {
    //   Serial.println("blue");
    // } else if (color == 3) {
    //   Serial.println("yellow");
    // }


    //call the ambient light snesor and adjust LEDs depending on the timedelaya nd the period
    lightDetect.DetectLight(counter);

    //call battery sensor code and adjust LEDs

    //call a bot function
    robo.forward(100);




    /***********************************************/

    do {
      cur_time = micros();
      //Serial.println(counter);
    } while (cur_time - prev_time < TimeDelay);

    counter = (counter >= period) ? 0 : (counter + 1);
}

