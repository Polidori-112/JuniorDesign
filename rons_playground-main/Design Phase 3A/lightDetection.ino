#define color_pin A2

void setup() {
  pinMode(color_pin, INPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  Serial.begin(9600);
  digitalWrite(19,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int red = 0;
  int blue = 0;
  digitalWrite(4,HIGH);
  digitalWrite(3,LOW);
  blue = analogRead(color_pin);
  delay(40);

  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  red = analogRead(color_pin);
  delay(40);

  // Serial.print("red: ");
  // Serial.print(red);
  // Serial.print(" ");
  // Serial.print("blue: ");
  // Serial.println(blue);
  if (red > 800) {
    if (blue > 680) {
      Serial.println("yellow");
    }else{
      Serial.println("red");
    }
  } else {
    if (blue > 550) {
      Serial.println("blue");
    }else{
      Serial.println("black");
    }
  }


}


