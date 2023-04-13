#define batteryReader A0
#define RED_LED 9
#define GREEN_LED 10
#define BLUE_LED 11

int value = 0;
int brightness = 0;
float voltage;
float R2 = 1000.0;
float R1 = 2000.0;

#define M1CTL 5
#define M1A 2
#define M1B 4

#define M2CTL 6
#define M2A 7 
#define M2B 3

#define distIn A4
#define distOut 8

struct color {int val; int mag;};


unsigned long time_now;

#include <SPI.h>
#include <WiFiNINA.h>


char server[] = "ee31.ece.tufts.edu";
WiFiClient client;
//String resourcePath = "/hexString/command";
String resourcePath = "/time";
int port = 80; 

int keyIndex = 0;                // your network key Index number (needed only for WEP)

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
static char messageData[255 + 1];


void setup() {
  
  pinSetup();
  Serial.begin(9600);

  digitalWrite(13, HIGH);

}

void loop() {
  // backward(100, 1000);
  // delay(1000);
  // crank90_L();
  // crank90_R();

  //Robot 1 gets request
  forwards(250);

  delay(750);  

}
void forwards(int ms) {
  // Set forward direction
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, HIGH);
  digitalWrite(M2B, LOW);
  digitalWrite(M2A, HIGH);

  // Turn motor on 
  analogWrite(M1CTL, 76);
  analogWrite(M2CTL, 75);
  delayCheck(ms);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0);
}
void readData() {
  String response = getRequest();
  //Serial.print("Response: ");
  //Serial.println(response);
  //Serial.println("End.\n");

  if (response == "penis") {
    forward(100, 1000);
  }
  if (response == "back") {
    backward(100, 1000);
  }
  if (response == "left") {
    crank90_L();
  }
  if (response == "right") {
    crank90_R();
  }
  else stop();
}

void delayCheck(int delay) {
  int time_now = millis();
  //perform all checks in this loop
  while (millis() < (time_now + delay)) {
    //if analogRead((distIn < 100)) return;
      if (analogRead(distIn) > 100)
      digitalWrite(distOut, HIGH);
  else {
    digitalWrite(distOut, LOW);
    stop();
    return;
  }


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

  digitalWrite(13, LOW);
}

void blinkFunction() {
  Serial.println("I'm blinking.");
  while (true) {
    digitalWrite(10, HIGH);
    delay(500);  
    digitalWrite(10, LOW);
    delay(500);     
  }
}

//F392FC86D8D7
void postRequest(char *message) {
  Serial.print("Sending post request: ");
  Serial.println(message);
  Serial.println("");
  delay(300); 
  if (client.connect(server,80)) { 
    //Serial.println("POST request");
    //this robot is F392FC86D8D7, the other robot is 4A9EDB0160D5 
    client.println("POST /F392FC86D8D7/4A9EDB0160D5 HTTP/1.1");
    client.println("Host: ee31.ece.tufts.edu");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(strlen(message));
    client.println();
    client.print(message);
    client.println("Connection: close");
    client.println();
  }
  delay(5000);
}

String getRequest() {
  Serial.println("GET Request");
  if (client.connect(server,80)) {
    Serial.println("Client Connected");
    //this robot is F392FC86D8D7, the other robot is 4A9EDB0160D5 
    client.println("GET /F392FC86D8D7/4A9EDB0160D5 HTTP/1.1");
    client.println("Host: ee31.ece.tufts.edu");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("connection failed");
  }

  delay(300);

  // int reading = client.read();
  // while (reading != -1) {
  //   Serial.print((char) reading);
  //   reading = client.read();
  // }

  int reading = client.read();
  int secondReading = 0;
  int idx = 0;

  while(reading != -1) {
    if (reading == 13 && secondReading == 10) {
      break;
    }
    secondReading = reading; 
    reading = client.read();
  }

  while(reading != -1 && idx < 255) {
      messageData[idx] = reading;
      idx++;
      reading = client.read();
    }
    messageData[idx] = '\0'; 
    //Serial.write(messageData);
  
  //delay(5000); 

  //Convert messageData into a string
  String messageString = String(messageData);

  //Parse messageData. "senderID=F392FC86D8D7&receiverID=F392FC86D8D7&message=Success&MYMESSAGE.="
  int startIndex = messageString.indexOf("Success&") + 8;
  int endIndex = messageString.length() - 1;

  // Extract the substring between the start and end indexes
  String parsedMessage = messageString.substring(startIndex, endIndex);

  // Print the extracted string
  //Serial.println(parsedMessage);
  return parsedMessage;
}

void printWifiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}
