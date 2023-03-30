void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);  // Initialize the serial output
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int num = analogRead(A0);
  if (num > 360) {Serial.println('1'); digitalWrite(6, HIGH);}
  else Serial.println('0');
}
