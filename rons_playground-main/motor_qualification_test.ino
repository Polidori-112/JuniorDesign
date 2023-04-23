void setup() {
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
}

void loop() {
  right();
  delay(10000);
  stop();
  delay(1000);
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
