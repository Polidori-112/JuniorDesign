#define batteryReader A0
#define RED_LED 9
#define GREEN_LED 10
#define BLUE_LED 11

unsigned long PREVIOUS_BAT = 0;  // will store last time battery 
long BAT_INTERVAL = 1000;  // interval at which to check battery. Default: 10000

int value = 0;
float voltage;
float R1 = 2000.0;
float R2 = 1000.0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  batteryRead();
}

void batteryRead() {
  if (millis() % 3000 == 0) {
    voltage = analogRead(batteryReader) * (5.0/1024)*((R1 + R2)/R2);
    Serial.print("Voltage =");
    Serial.println(voltage);

    // if (voltage >= 6) {
    //   digitalWrite(GREEN_LED, HIGH);
    //   digitalWrite(RED_LED, LOW);
    //   digitalWrite(BLUE_LED, LOW);
    // }
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

//6.35

