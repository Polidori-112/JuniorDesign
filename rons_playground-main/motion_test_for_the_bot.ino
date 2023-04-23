struct Motor {
  int PinA;
  int PinB;
  bool rev;
};

Motor motor1 = {9,10,false};
Motor motor2 = {5,6,true};


void setup() {

  pinMode(motor1.PinA, OUTPUT);
  pinMode(motor1.PinB, OUTPUT);
  pinMode(motor2.PinA, OUTPUT);
  pinMode(motor2.PinB, OUTPUT);
}

void loop() {
  int speed = 100;
  drive(motor1, speed);
  drive(motor2, speed);
}

void drive(Motor mtr, int speed){
  if(mtr.rev){
    analogWrite(mtr.PinA,speed);
    digitalWrite(mtr.PinB,LOW);
  }else{
    digitalWrite(mtr.PinA,LOW);
    analogWrite(mtr.PinB,speed);
  }
}
