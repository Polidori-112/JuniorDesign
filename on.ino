// STATE: ON
// led is red, blinks at 10hz

#define RED_LED 11
// ON SETUP
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 100; // interval of blinking is at 100ms (10hz)
int ledState = LOW;  // ledState used to set the LED

void setup() {
    // initialize digital pin LED_BUILTIN as an output.
  pinMode(RED_LED, OUTPUT);
}

void loop() {
  on();
}

//blinks at 10hz 
void on(){ 
  unsigned long currentMillis = millis(); // curent time 
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(RED_LED, ledState);
  }
}