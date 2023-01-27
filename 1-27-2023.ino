int on = 0;
int off = 1;
float v_on;
float v_off;
int potentiometerPin = A0;   // potentiometer connected to analog pin A0

//BLUE LED STUFF
int BLUE_LED_STATE = LOW;  // ledState used to set the LED
unsigned long PREVIOUS_BLUE = 0;  // will store last time LED was updated
long BLUE_INTERVAL = 100;  // interval at which to blink (milliseconds). Default: 100

//default switch values, 1 is OPEN (HIGH), 2 is CLOSED (LOW)
int PREV_SWITCH_1 = HIGH;
int PREV_SWITCH_2 = LOW;

#define RED_LED 9
#define GREEN_LED 10
#define BLUE_LED 11

#define ON_BUTTON 2
#define OFF_BUTTON 3

#define SWITCH_1 4 //LEFT SWITCH
#define SWITCH_2 5 //RIGHT SWITCH


void setup() {
  // Setting up pin modes
  pinMode(on, INPUT_PULLUP);
  pinMode(off, INPUT_PULLUP);
  pinMode(ON_BUTTON, INPUT);
  pinMode(OFF_BUTTON, INPUT);
  pinMode(SWITCH_1, INPUT_PULLUP);
  pinMode(SWITCH_2, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(on_pressed()) {
    runState();
  }
}

// reads the potentiometer and maps its value to a range from 0 to 255
int read_potentiometer() {
  int potentiometerValue = analogRead(potentiometerPin); 
  int mappedValue = map(potentiometerValue, 0, 1023, 0, 255);  
  //Serial.println("Potentiometer: "); 
  //Serial.print(mappedValue);
  return mappedValue;
}

// ON will be pressed if digitalRead is LOW
bool on_pressed() {
    // v_on = digitalRead(on);
    // if (v_on == 1.0) {
    //   return true;
    // }
    // return false;

    digitalWrite(ON_BUTTON, HIGH);
    if (digitalRead(ON_BUTTON) == LOW) {
      Serial.println("ON");
      return true;
    }
    return false;
  }

bool off_pressed() {
    // v_off = digitalRead(off);
    // if (v_off == 1.0) {
    //   return true;
    // }
    // return false;
    digitalWrite(OFF_BUTTON, HIGH);
    if (digitalRead(OFF_BUTTON) == LOW) {
      Serial.println("OFF");
      return true;
    }
    return false;
  }

bool both_pressed() {
    v_on = digitalRead(on);
    v_off = digitalRead(off);
    if (v_on == 1.0 && v_off == 1.0) {
      return true;
    }
    return false;
}

//default: delay of 0.1s (10 times per second). After switch, changes to 
//delay of 1s (1 time per second)
void blue_led_blink() {
  unsigned long CURRENT_BLUE = millis();
  if (CURRENT_BLUE - PREVIOUS_BLUE >= BLUE_INTERVAL) {
    // save the last time you blinked the LED
    PREVIOUS_BLUE = CURRENT_BLUE;

    // if the LED is off turn it on and vice-versa:
    if (BLUE_LED_STATE == LOW) {
      BLUE_LED_STATE = HIGH;
    } else {
      BLUE_LED_STATE = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(BLUE_LED, BLUE_LED_STATE);
  }
}

void runState() {
  int red_T = 50;
  float fade = 255;
  bool red_on;
  for (int i = 0; i < 7500; i++) {
    delay(1);
    //blue led blinking (changed when switch 1 is close)
    blue_led_blink();
    
    //flash red led
    if ((i % red_T) == 0)
      red_on = !red_on;
    
    if (red_on)
      analogWrite(RED_LED, 255);
    else
      digitalWrite(RED_LED, LOW);

    //green led fade
    if (i < 6000) {
      fade = fade - (0.0425);
      //Serial.println(fade);
      //Serial.println(i);
      analogWrite(GREEN_LED, (int)fade);
    }
    //green led flash
    else {
      if (((i < 6500) or (i > 7000)))
        analogWrite(GREEN_LED, 255);
      else if (((i > 6500) or (i < 7000)))
        digitalWrite(GREEN_LED, LOW);
    }
    // Check state of switches. 
    check_switches();

    //Reads potentiometer
    read_potentiometer();

    // If off button is pressed, go to sleep
    if (off_pressed()) {
      sleep();
    }
  }
  runState();  
}

//Blinks blue led for 1s then fades. Goes to OFF state. 
void sleep() {
  bool fade = true; 
  unsigned long BLINK_PERIOD = 1000; // set fadetime in ms

  //blinks @ 4hz 4 times (1 sec)
  for (int i = 0; i <= 4; i++) {
    digitalWrite(BLUE_LED, HIGH);
    delay(125);
    analogWrite(BLUE_LED, LOW);
    delay(125);
  }

  // define starting fade time
  unsigned long fadeStartTime = millis();

  // fade for 1s
  while (fade == true) {
    unsigned long FADE_PERIOD = 1000; // set fadetime in ms
    unsigned long progress = millis() - fadeStartTime;

    if (progress <= FADE_PERIOD) {
      long brightness = map(progress, 0, FADE_PERIOD, 255, 0);
      analogWrite(BLUE_LED, brightness);
    }
    else {
      fade = false; 
    }
  }
  //Turns off
  off_state();
}

// OFF STATE. Turns off all leds, waits for ON button.
void off_state() { 
  while (on_pressed() == false) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }
  runState();
}

void check_switches() {
  int SWITCH_1_STATE = digitalRead(SWITCH_1);
  int SWITCH_2_STATE = digitalRead(SWITCH_2);
  //if switches didnt change, nothing happens
  if ((PREV_SWITCH_1 == SWITCH_1_STATE) and (PREV_SWITCH_2 == SWITCH_2_STATE)) {
    return;
  }
  PREV_SWITCH_1 = SWITCH_1_STATE; 
  PREV_SWITCH_2 = SWITCH_2_STATE;


  // else check states
  //SWITCH 1 IS CLOSED
  if (SWITCH_1_STATE == LOW) {
    Serial.println("SWITCH_1 CLOSED");
    BLUE_INTERVAL = 1000;
  }
  else {
    BLUE_INTERVAL = 100;
  }

  //SWITCH 2 IS OPEN
  if (SWITCH_2_STATE == HIGH) {
    Serial.println("SWITCH_2 OPEN");
    //interrupt runs until interval changes or switch 2 closes
    while ((BLUE_INTERVAL == 1000) and (digitalRead(SWITCH_2) == HIGH)) {
       if (digitalRead(SWITCH_1) == HIGH) {
        Serial.println("SWITCH_1 OPEN");
        BLUE_INTERVAL = 100;
      }
      digitalWrite(RED_LED, HIGH);
    }
  }

  // //BOTH SWITCHES OFF
  // if ((SWITCH_1_STATE == HIGH) && (SWITCH_2_STATE == HIGH)) {
  //   Serial.println("SWITCH_1 OFF | SWITCH_2 OFF");
  //   if (BLUE_INTERVAL == 1000) {
  //     //TODO: an interrupt is triggered only if the flash rate of the BLUE LED is ten 
  //     //times per second, by turning on a RED LED
  //     while (true) {
  //       digitalWrite(RED_LED, HIGH); 
  //     }
  //   }
  //   return; 
  // }  
  // //SWITCH_1 ON
  // else if ((SWITCH_1_STATE == LOW) && (SWITCH_2_STATE == HIGH)) {
  //   Serial.println("SWITCH_1 ON | SWITCH_2 OFF");
  //   BLUE_INTERVAL = 100; //changes rate of blue LED blinking bc 1 is ON
  // }  
  // //SWITCH_2 ON
  // else if ((SWITCH_1_STATE == HIGH) && (SWITCH_2_STATE == LOW)) {
  //   BLUE_INTERVAL = 1000; //changes rate of blue LED blinking bc switch 1 is off
  //   Serial.println("SWITCH_1 OFF | SWITCH_2 ON");
  // }  
  // //BOTH ON
  // else if ((SWITCH_1_STATE == LOW) && (SWITCH_2_STATE == LOW)) {
  //   Serial.println("SWITCH_1 ON | SWITCH_2 ON");
  //   BLUE_INTERVAL = 100; //changes rate of blue LED blinking bc 1 is ON
  // }  
}
