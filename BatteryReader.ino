#define batteryReader A0
#define RED_LED 9
#define GREEN_LED 10
#define BLUE_LED 11

int value = 0;
int brightness = 0;
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
    //map battery into values from 0 to 255
    brightness = map(value, 3, 6.4, 0, 255);
    analogWrite(GREEN_LED, brightness);

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

