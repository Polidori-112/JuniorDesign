#define M1CTL 9
#define M1A 8
#define M1B 7

#define M2CTL 5
#define M2A 4 
#define M2B 2

void setup() {
  // put your setup code here, to run once:
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M1CTL, OUTPUT);
  digitalWrite(M1CTL, LOW);
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  forward(255, 1000);
  forward(125, 1000);

}

//p is out of 255
void forward(int p, int ms) {
  // Set forward direction
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, HIGH);
  
  // Turn motor on 
  analogWrite(M1CTL, p);
  analogWrite(M2CTL, p)
  delay(ms);
  analogWrite(M1CTL, 0);
  analogWrite(M1CTL, 0);

}
