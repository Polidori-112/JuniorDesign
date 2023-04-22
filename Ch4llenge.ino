
#define batteryReader A0
#define RED_LED 9
#define GREEN_LED 10
#define BLUE_LED 11

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
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);


}

void loop() {
  // backward(100, 1000);
  // delay(1000);
  // crank90_L();
  // crank90_R();

  //Robot 1 gets request
  followYellow(0);
  delay(1000);

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




/*Code Below here shouldn't be used*/






















void batteryRead() {
  if (millis() % 3000 == 0) {
    voltage = analogRead(batteryReader) * (5.0/1024)*((R1 + R2)/R2);
    Serial.print("Voltage =");
    Serial.println(voltage);
    //map battery into values from 0 to 255
    brightness = map(value, 3, 6.4, 0, 255);
    analogWrite(GREEN_LED, brightness);

    if (voltage <= 4.8) {
      analogWrite(GREEN_LED, 0);
    }
    else if (voltage <= 5.5) {
      analogWrite(GREEN_LED, 155);
    }
    else {
      analogWrite(GREEN_LED, 255);
    }
    // else if (voltage >= 5) {
    //   digitalWrite(GREEN_LED, LOW);
    //   digitalWrite(RED_LED, LOW);
    //   digitalWrite(BLUE_LED, HIGH);
    // }
    // else {
    //   digitalWrite(GREEN_LED, LOW);
    //   digitalWrite(RED_LED, HIGH);
    //   digitalWrite(BLUE_LED, LOW);
    // }
  }
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

