//power.h
#include "Power.h"

Power::Power() {

}

Power::Power_set(int pin1, int pin2) {
  pinArdu = pin1;
  pinBread = pin2;
  init();
}

Power::init(){
  pinMode(pinArdu, INPUT_PULLUP);
  pinMode(pinBread, INPUT_PULLUP);
}

Power::readPower() {
  voltArdu = (analogRead(pinArdu) * 5.0) / 1024.0;
  voltBread = (analogRead(pinBread) * 5.0) / 1024.0;
  if (voltArdu >= 4.165) {
    levelArdu = 2;
  }
  else if (voltArdu >= 3.7475) {
    levelArdu = 1;
  }
  else {
    levelArdu = 0;
  }
  if (voltBread >= 4.165) {
    levelBread = 2;
  }
  else if (voltBread >= 3.7475) {
    levelBread = 1;
  }
  else {
    levelBread = 0;
  }
}
