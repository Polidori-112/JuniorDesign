#define switch1 8
#define switch2 11
#define switch3 12
#define switch4 13
#define potent1 A0
#define potent2 A1

#define redLED 10
#define greenLED 6
#define blueLED 5

#define butt1 4
#define butt2 3

unsigned long startMillis = millis();
unsigned long currMillis;
int currState; //Off: 0, On: 1, Diagnostic: 2, Run: 3, Sleep: 4
int prevState = 0;
int problems = 8;

bool insleep = false;
bool indiag = false;
bool blueTen = false;
bool redON = false;

void setup() {
  pinMode(switch1,INPUT_PULLUP);
  pinMode(switch2,INPUT_PULLUP);
  pinMode(switch3,INPUT_PULLUP);
  pinMode(switch4,INPUT_PULLUP);

  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(blueLED,OUTPUT);

  pinMode(butt1, INPUT_PULLUP);
  pinMode(butt2, INPUT_PULLUP);

  Serial.begin(9600);

  attachInterrupt(butt1, changeBlueTen, FALLING);
  attachInterrupt(butt2, change, FALLING);

}

void loop() {
  checkState();
  prevState = currState;

  if ((digitalRead(8) == 0) and (digitalRead(11) == 1) and (digitalRead(12) == 1) and (digitalRead(13) == 1)) {
    insleep = false;
    indiag = false;
    on();

  }else if ((digitalRead(8) == 1) and (digitalRead(11) == 0) and (digitalRead(12) == 1) and (digitalRead(13) == 1)) {
    insleep = false;
    diagnostic();
  }else if ((digitalRead(8) == 1) and (digitalRead(11) == 1) and (digitalRead(12) == 0) and (digitalRead(13) == 1)) {
    indiag = false;
    sleep();
  }else if ((digitalRead(8) == 1) and (digitalRead(11) == 1) and (digitalRead(12) == 1) and (digitalRead(13) == 0)) {
    insleep = false;
    indiag = false;
    // digitalWrite(9,LOW); 
    // digitalWrite(5,LOW);
    // digitalWrite(6,HIGH);
    run();

  }else{
    insleep = false;
    indiag = false;
  }
}

void on()
{
  blink(10,10,analogRead(potent2)/4);
}

void blink(int pin, int f, int brightness)
{

  int del = 500 / f;
  analogWrite(pin,brightness);
  delay(del);
  digitalWrite(pin,0);
  delay(del);
}


void sleep()
{
  if (not insleep) {
    for (int i=0; i< 4; i++) {
      blink(blueLED, 4, analogRead(potent2)/4);
    }
    fade(blueLED, 1000, analogRead(potent2)/4);
    insleep = true; 
  }
}

void checkState() {
  if ((digitalRead(8) == 0) and (digitalRead(11) == 1) and (digitalRead(12) == 1) and (digitalRead(13) == 1)) {
    currState = 1;
  }else if ((digitalRead(8) == 1) and (digitalRead(11) == 0) and (digitalRead(12) == 1) and (digitalRead(13) == 1)) {
    currState = 2;
  }else if ((digitalRead(8) == 1) and (digitalRead(11) == 1) and (digitalRead(12) == 0) and (digitalRead(13) == 1)) {
    currState = 3;
  }else if ((digitalRead(8) == 1) and (digitalRead(11) == 1) and (digitalRead(12) == 1) and (digitalRead(13) == 0)) {
    currState = 4;
  }else{
    currState = 0;
  }
}


void fade(int pin, int f, int b) {
  int s = -2; //speed of decay
  int del = f / (256 / abs(s));
  startMillis = millis();
  currMillis = startMillis;
  while (currMillis - startMillis <= f) {
    analogWrite(pin, b);
    b = b + s;
    delay(del);
    checkState();
    currMillis = millis();
    if (!(prevState == currState)) {
      Serial.println("State changed in Fade");
      analogWrite(pin, 0);
      break;
    }
  }
}

void diagnostic() {
  // startMillis = millis();
  // currMillis = startMillis;
  // while (currMillis - startMillis <= problems * 1000) {
  //   blink(10, 1, analogRead(potent2)/4);
  //   checkState();
  //   if (!(prevState == currState)) {
  //     Serial.println("State changed in Diagnostic Blink");
  //     analogWrite(10, 0);
  //     break;
  //   }
  // }
  if (not indiag){
    for(int i = 0; i < problems; i++){
      blink(10, 1, analogRead(potent2)/4);
    }
  }
  indiag = true;
}

void run(){
  startMillis = millis();
  currMillis = startMillis;
  int s = -2; //speed of decay in fade
  int b = 255; //custome bright somehow later
  while (currMillis-startMillis <= 8000) {
    if (blueTen) {
      if ((currMillis - startMillis) % 100 > 50){
        analogWrite(blueLED, analogRead(potent2)/4);
      }else{
        analogWrite(blueLED, 0);
      }
    }else{
      if ((currMillis - startMillis) % 1000 > 500){
        analogWrite(blueLED, analogRead(potent2)/4);
      }else{
        analogWrite(blueLED, 0);
      }  
    }
    if(redON){
      analogWrite(redLED, analogRead(potent2)/4);
    }else{
      analogWrite(redLED, 0);
    }

  if ((currMillis - startMillis) < 6000) {
    // del = 6000 / (b / abs(s));
    // if ((currMillis - startMillis))
    // analogWrite(greenLED, )
    // if ()
    analogWrite(greenLED, (6000 - (currMillis - startMillis))/23);
    Serial.println((6000 - (currMillis - startMillis))/23);

  }else{
    if ((currMillis - startMillis) < 6500 or ((currMillis - startMillis) < 7500 and (currMillis - startMillis) > 7000)){
      analogWrite(greenLED, analogRead(potent2)/4);
    }else {
      analogWrite(greenLED, 0);
    }
  }

    currMillis = millis();
  }


}


void changeBlueTen() {
  blueTen = !blueTen;
}

void change(){
  if(blueTen){
    //analogWrite(redLED, analogRead(potent2)/4);
    redON = !redON;
  }else{
    redON = false;
  }
}

