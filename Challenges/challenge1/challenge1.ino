#define batteryReader A0
#define RED_LED 8
#define GREEN_LED 9
#define YELLOW_LED 10
#define SPEAKER 11

int value = 0;
int brightness = 0;
float voltage;
float light_level;
float R2 = 1000.0;
float R1 = 2000.0;

//motor control
#define M1CTL 5
#define M1A 2
#define M1B 4

#define M2CTL 6
#define M2A 7 
#define M2B 3

//distance sensor
#define distIn A4
#define distOut 8

//color sensor
#define B_col 13
#define R_col 12
#define col A5

//headlights
#define photo A0
#define head 0
#define tail 1

#define light_thresh 100

struct color {int val; int mag;};

void setup() {
  
  pinSetup();
  Serial.begin(9600);


  // flash blue and red LEDs 3 times
  for (int i = 0; i < 3; i++) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    delay(500);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, HIGH);
    delay(500);    
  }
  
  // moves forward until collision detector
  forward(100, 10000);

  // turns 180
  crank90_L();
  crank90_L();

  // find red and flash red 
  while (findColor() != 0) {
    forward(80, 200);
  }
  stop();
  digitalWrite(RED_LED, HIGH);
  delay(1000);
  digitalWrite(RED_LED, LOW);

  // light based communication
  generateOutput('4');

}


void loop() {

}

void generateOutput(char input[]) {
  int num;
  for (int i = 0; i < 8; i++) {
    if (input[i] == '1') {
      // generate a 3kHz wave for 1/8 second
      for (int j = 0; j < 3000 / 8; j++) {
        digitalWrite(10, HIGH);
        delayMicroseconds(166);
        digitalWrite(10, LOW);
        delayMicroseconds(166); 
      }
    } else {
      // output low for 1/8 second
      digitalWrite(10, LOW);
      delay(125);
      //modDelay(125);
    }
    // Read the output
    //readOutput();
  }
}

void delayCheck(int d) {
  int time_now = millis();
  //perform all checks in this loop
  while (millis() < (time_now + d)) {
    // collision sensor
    // if (analogRead(distIn) > 100)
    //   digitalWrite(distOut, HIGH);
    // else {
    //   digitalWrite(distOut, LOW);
    //   stop();
    //   return;
    // }
    //headlight sensor
    light_level = analogRead(photo);
    light_level = light_level * (6.0 / 1023.0); 
    Serial.println(light_level);
    if(light_level <= 4.5)
      doCh4llenge();
  }
  return;
}


void followYellow(int val) {
  int reference;
  int curr;
  digitalWrite(B_col, HIGH);
  digitalWrite(R_col, HIGH);
  delayCheck(100); 
  if (!val)
    reference = analogRead(col);
  else
    reference = val;
  curr = 0;
  int x = reference;
  while (curr < 20 && curr > -20) {
    //skkkrrrrrrrrtttt a little to the right
    forwardish(100, 100);
    curr = reference - analogRead(col);;
  }
  reference = analogRead(col);
  curr = 0;
  while (curr < 10 && curr > -10) {
    pivot_L(80, 50);
    delay(50);
    curr = reference - analogRead(col);
  }
  followYellow(x);
  stop();
}

//p is out of 255
void forwardish(int p, int ms) {
  // Set forward direction
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, HIGH);
  digitalWrite(M2B, LOW);
  digitalWrite(M2A, HIGH);

  // Turn motor on 
  analogWrite(M1CTL, p);
  analogWrite(M2CTL, p + 25);
  delayCheck(ms);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0);
}

void doCh4llenge() {
  stop();
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
  digitalWrite(tail, LOW);
  while(1);
  crank90_L();
  followYellow(0);  
}

// returns 0 for red, 1 for yellow, 2 for blue, 3 for black
int findColor() {
  int color;
  bool red;
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);

  digitalWrite(B_col, LOW);
  digitalWrite(R_col, HIGH);
  delay(100);
  color = analogRead(col);
  //Serial.println(color);
  if (280 > color)
    red = true;
  else
    red = false;

  digitalWrite(B_col, HIGH);
  digitalWrite(R_col, LOW);
  delay(100);
  color = analogRead(col);
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

void pinSetup() {
  pinMode(distOut, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(B_col, OUTPUT);
  pinMode(R_col, OUTPUT);
  
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M1CTL, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M2CTL, OUTPUT);
  digitalWrite(M1CTL, LOW);
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2CTL, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);

  pinMode(photo, INPUT);
  pinMode(head, OUTPUT);
  pinMode(tail, OUTPUT);
  digitalWrite(head, HIGH);
  digitalWrite(tail, LOW);
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
  delayCheck(ms);
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
  pivot_R(77, 800);
}

void crank90_L() {
  pivot_L(77, 800);
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

void pivot_L(int p, int ms) {
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

void pivot_R(int p, int ms) {
   // Set backward direction
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, HIGH);
  digitalWrite(M2B, LOW);
  digitalWrite(M2A, HIGH);

  analogWrite(M1CTL, p);
  analogWrite(M2CTL, p);
  delay(ms);
  digitalWrite(M1CTL, 0);
  digitalWrite(M2CTL, 0);  
}

void stop() {
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2B, LOW);
  digitalWrite(M2A, LOW);

  digitalWrite(M1CTL, 0);
  digitalWrite(M2CTL, 0);  
}