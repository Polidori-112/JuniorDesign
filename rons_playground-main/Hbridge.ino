void setup() {
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
}

void loop() {
  right();
  delay(3000);
  left();
  delay(3000);
  stop();
  delay(3000);
}

void left(){
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);

}

void right(){
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
}

void stop(){
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
}
