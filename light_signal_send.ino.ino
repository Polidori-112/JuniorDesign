#define M1CTL 5
#define M1A 8
#define M1B 7

#define M2CTL 9
#define M2A 4 
#define M2B 2

#define photo A1
#define nite 3
float med = 1.5;
float lo = 2.5;

int ledP = 50;

struct color {int val; int mag;};
color val;

unsigned long time_now;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M1CTL, OUTPUT);
  pinMode(nite, OUTPUT);
  pinMode(photo, INPUT);
  digitalWrite(M1CTL, LOW);
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  Serial.begin(9600);
}

void loop() {
  //Serial.println(analogRead(A0));
  //Serial.println(findColor());
  //digitalWrite(12, LOW);
  //digitalWrite(13, HIGH);
  //forward(100, 100);
  if (findColor() == 2) forward(100, 100);
  else{
    turn_R(150, 900);
    while(findColor() != 3) forward(100, 100);
  
    delay(100000);
  }

  float light_level = analogRead(photo);
  light_level = light_level * (5.0 / 1023.0);
  //Serial.println(light_level);

  if (light_level >= lo) { 
    ledP = 1;
  } else {
    ledP = 50;
  }

  
  Serial.println(val.val);
}


// void followTape(color reference) {
//   if (reference.val != 2)
//     return;
//   digitalWrite(12, LOW);
//   digitalWrite(13, HIGH);
//   delay(100);
//   reference.mag = getColor();
//   int col = reference.mag - getColor();
//   while (col < 10 && col > -10) {
//     //skkkrrrrrrrrtttt
//     forward(100, 100);
//     col = reference.mag - getColor();
//   }
//   for (int i = 0; i < 20; i++) {
//     int c = findColor();
//     if (c == 2) {
//       followTape(reference);
//       return;
//     }
//     pivot_L(100, 100);
//   }
//   crank90_R();
//   while(findColor() != 2)
//     pivot_R(100, 100);
//   stop();
// }

void delayCheck(int delay) {
  int time_now = millis();
  //perform all checks in this loop
  int curr = millis();
  int next = 0;
  for (int i = 0; curr < (time_now + delay); i++) {
    curr = millis();
    if (i % ledP == 0) {
      if (digitalRead(nite) == 0) { 
        digitalWrite(nite, HIGH);
      } else {
        digitalWrite(nite, LOW);
      }
    }
        
    while(next < curr + 1)
      next = millis();      
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

  analogWrite(M1CTL, p / 4);
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
