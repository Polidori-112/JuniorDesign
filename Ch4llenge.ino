#define photo A0
#define head 5
#define tail 6

void setup() {
  // put your setup code here, to run once:
  pinMode(photo, INPUT);
  pinMode(head, OUTPUT);
  pinMode(tail, OUTPUT);
  digitalWrite(head, HIGH);
  digitalWrite(tail, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float light_level = analogRead(photo);
  light_level = light_level * (5.0 / 1023.0); 
  Serial.println(light_level);

  if(light_level <= 4.0) {
    doCh4llenge();
  }
  digitalWrite(tail, LOW);
}

void doCh4llenge() {
  digitalWrite(head, LOW);
  delay(250);
  digitalWrite(head, HIGH);
  delay(250);
  digitalWrite(head, LOW);
  delay(250);
  digitalWrite(head, HIGH);
  delay(500);
  digitalWrite(tail, HIGH);
  delay(1000);
}
