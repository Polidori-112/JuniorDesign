// STATE: SLEEP
#define BLUE_LED 9

void setup() {
  // put your setup code here, to run once:
  pinMode(BLUE_LED, OUTPUT);
  blinkOneSec();
}

void loop() {
  //Blue blinks @ 4 Hz (0.25s delay) for 1 sec, Fade for 1 sec.
    
	// Last blink fades to off over Fade.
}

void blinkOneSec() {
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

}