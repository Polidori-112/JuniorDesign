#define M1CTL 5
#define M1A 8
#define M1B 7

#define M2CTL 9
#define M2A 4 
#define M2B 2

struct color {int val; int mag;};


unsigned long time_now;
void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M1CTL, OUTPUT);
  digitalWrite(M1CTL, LOW);
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  Serial.begin(9600);

}

void loop() {
  //Serial.println(analogRead(A0));
  //Serial.println(findColor());
  color val;
  //forward(100, 100);
  val.mag = getColor();
  val.val = findColor();
  //Serial.println(val.mag);
  followBlue(val);
  delayCheck(1000);
}

void delayCheck(int delay) {
  int time_now = millis();
  //perform all checks in this loop
  while (millis() < (time_now + delay)) {



  }
  return;
}

// void findBlue(color ref1, color ref2, bool left) {
//   color curr;
//   curr.val = 1;
//   curr.mag = getColor();
//   if ((curr.mag - ref1.mag)/10 < (ref2.mag - ref1.mag)/10) {
//     if (left) {
//       pivot_L(100, 100);
//       findBlue(ref1, curr, left);
//     } else
//       pivot_R(100, 100);
//   } else {
//     if (left)
//       pivot_R(100, 100);
//     else
//       pivot_L(100, 100);
//   }
//   findBlue(ref1, curr, left);
       
  
// }

void followRed(color reference) {
  if (reference.val)
    return;
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  delayCheck(100);  
  int col = reference.mag - getColor();
  Serial.println(col);
  while (col < 10 && col > -10) {
    //skkkrrrrrrrrtttt
    forward(100, 100);
    col = reference.mag - getColor();  
  }

  
  stop();
}

void followBlue(color reference) {
  if (reference.val != 2)
    return;
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  delayCheck(100);  
  int col = reference.mag - getColor();
  Serial.println(col);
  while (col < 10 && col > -10) {
    //skkkrrrrrrrrtttt
    forward(100, 100);
    col = reference.mag - getColor();
  }
  while(findColor() != 2)
    pivot_L(100, 100);
  stop();
}

// returns 0 for red, 1 for yellow, 2 for blue, 3 for black
int findColor() {
  int color;
  bool red;
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  delayCheck(100);
  color = getColor();
  //Serial.println(color);
  if (280 > color)
    red = true;
  else
    red = false;

  
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  delayCheck(100);
  color = getColor();
  //Serial.println(color);
  if (color > 540 && color < 600)
    return 2;
  else if (color < 540 && red)
    return 1;
  else if (red)
    return 0;
  else
    return 3;
}


int getColor() {
  return analogRead(A0);
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
  pivot_R(77, 1000);
}

void crank90_L() {
  pivot_L(77, 1000);
}

void turn_L(int p, int ms) {
   // Set backward direction
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, HIGH);
  digitalWrite(M2B, LOW);
  digitalWrite(M2A, HIGH);

  analogWrite(M1CTL, p);
  analogWrite(M2CTL, p/2);
  delay(ms);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0);  
}

void turn_R(int p, int ms) {
   // Set backward direction
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, HIGH);
  digitalWrite(M2B, LOW);
  digitalWrite(M2A, HIGH);

  analogWrite(M1CTL, p / 2);
  analogWrite(M2CTL, p);
  delay(ms);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0);  
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


