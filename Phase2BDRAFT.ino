#define M1CTL 5
#define M1A 8
#define M1B 7

#define M2CTL 9
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

//

void loop() {
  // put your main code here, to run repeatedly:
  // forward(125, 1000);
  // delay(1000);
  // backward(125, 1000);
  crank90_R();
  crank90_R();
  crank90_R();
  crank90_R();
  crank90_R();
  crank90_R();
  crank90_R();
  crank90_R();
  crank90_R();
  crank90_R();
  crank90_R();
  crank90_R();
  delay(1000);
  // forward(75, 1000);
  // forward(75, 1000);
  // delay(1000);
  // backward(75, 1000);
  // delay(1000);    
}

//p is out of 255
void forward(int p, int ms) {
  // Set forward direction
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, HIGH);
  digitalWrite(M2B, LOW);
  digitalWrite(M2A, HIGH);

  // Turn motor on 
  analogWrite(M1CTL, p);
  analogWrite(M2CTL, p);
  delay(ms);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0);
}

void backward(int p, int ms) {
  // Set backward direction
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, HIGH);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, HIGH);

  // Turn motor on 
  analogWrite(M1CTL, p);
  analogWrite(M2CTL, p);
  delay(ms);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0);
}

void crank90_R() {
  pivot_R(71, 1000);
}

void crank90_L() {
  pivot_L(71, 1000);
}

void pivot_R(int p, int ms) {
   // Set backward direction
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, HIGH);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, HIGH);

  analogWrite(M1CTL, p);
  analogWrite(M2CTL, p);
  delay(ms);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0);  
}

void pivot_L(int p, int ms) {
   // Set backward direction
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, HIGH);
  digitalWrite(M2B, LOW);
  digitalWrite(M2A, HIGH);

  analogWrite(M1CTL, p);
  analogWrite(M2CTL, p);
  delay(ms);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0);  
}

void stop() {
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2B, LOW);
  digitalWrite(M2A, LOW);

  digitalWrite(M1CTL, 0);
  digitalWrite(M2CTL, 0);  
}
