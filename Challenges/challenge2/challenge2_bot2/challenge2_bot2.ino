//ZINNOBOT
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
#include "arduino_secrets.h" 
char server[] = "ee31.ece.tufts.edu";
WiFiClient client;
//String resourcePath = "/hexString/command";
String resourcePath = "/time";
int port = 80; 

int keyIndex = 0;                // your network key Index number (needed only for WEP)

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the WiFi radio's status

static char messageData[255 + 1];


void setup() {
  
  pinSetup();
  Serial.begin(9600);

  //movement_calibration();

  // Setup wifi
  wifiSetup();

  //Wait for other bot
  Serial.println("Sending START. waiting for START.");
  postRequest("START");
  waitFor("START");

  //Robot gets commands
  getAllCommands();
  
  //Robot sends commands
  sendCommands();
}

void loop() {

}

void getAllCommands() {
  for (int i = 0; i < 10; i++) {
    getCommands();
    delay(1000);
  }
}

void sendCommands() {
  Serial.println("Sending command 1: forward 12 inches");
  postRequest("FORWARD 2200");
  waitFor("BUSY");

  Serial.println("Sending command 2: full rotation");
  postRequest("FULLROTATION 0");
  waitFor("BUSY");

  Serial.println("Sending command 3: back 3 inches");
  postRequest("BACKWARD 600");
  waitFor("BUSY");

  Serial.println("Sending command 4: left");
  postRequest("LEFT 0");
  waitFor("BUSY");

  Serial.println("Sending command 5: move a bit");
  postRequest("FORWARD 500");
  waitFor("BUSY");

  Serial.println("Sending command 6: turn right");
  postRequest("RIGHT 0");
  waitFor("BUSY");

  Serial.println("Sending command 7: forward a lot");
  postRequest("FORWARD 2000");
  waitFor("BUSY");

  Serial.println("Sending command 8: turn right");
  postRequest("RIGHT 0");
  waitFor("BUSY");

  Serial.println("Sending command 9: turn right");
  postRequest("RIGHT 0");
  waitFor("BUSY");

  Serial.println("Sending command 10: backwards a bit");
  postRequest("BACKWARD 600");
  waitFor("BUSY");
}

void waitFor(String str) {
  while (getRequest() != str) {
    delay(100);  
  }
  Serial.println("OK received. Continuing."); 
}

void getCommands() {
  String getReq = getRequest();
  String outputWord, outputNumber;

  // Extract the action and number
  int spaceIndex = getReq.indexOf(' ');
  String action = getReq.substring(0, spaceIndex);
  String number = getReq.substring(spaceIndex + 1);

  Serial.print("Executing action: ");
  Serial.print(action);
  Serial.println(number);
  postRequest("BUSY");
  if (action == "FORWARD") {
    forward(100, number.toInt());
  }
  else if (action == "BACK") {
    backward(100, number.toInt());
  }
  else if (action == "LEFT") {
    crank90_L();
  }
  else if (action == "RIGHT") {
    crank90_R();
  }
  else if (action == "FULLROTATION") {
    fullrotation();
  }
  else {
    stop();
  }
  //Stop before next command
  stop();
}

void movement_calibration() {
  //Forward inches
  forward(100, 2200);
  delay(1000);

  //Full rotation
  fullrotation();
  delay(1000);

  // //Backwards
  backward(100, 600);
  delay(1000);

  //Turn left
  crank90_L();
  delay(1000);

  // Move a lil bit?
  forward(100, 500);
  delay(1000);

  //Turn Right
  crank90_R();
  delay(1000);

  //forwards 15
  forward(100, 2000);
  delay(1000);

  //Turn Right
  crank90_R();
  delay(1000);
  //Turn Right
  crank90_R();
  delay(1000);

  //Backwards a lil bit
  backward(100, 600);
  delay(1000);
}

void delayCheck(int delayT) {
  delay(delayT);
  // int time_now = millis();
  // //perform all checks in this loop
  // while (millis() < (time_now + delay)) {
  //   Serial.print("delay check. Delay:");
  //   Serial.print(delay);
  //   Serial.print("millis < time now + delay:");
  //   Serial.print(millis());
  //   Serial.print("<");
  //   Serial.print(time_now);
  //   Serial.print("+");
  //   Serial.println(delay);
    //if analogRead((distIn < 100)) return; //keep this commented out
    // distance stuff not working. Uncomment this later!
    // if (analogRead(distIn) > 100)
    //   digitalWrite(distOut, HIGH);
    // else {
    //   digitalWrite(distOut, LOW);
    //   stop();
    //   return;
    // }
  //}
  return;
}

void wifiSetup() {
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();
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

//p is out of 255
void forward(int p, int ms) {
  // Set forward direction
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, HIGH);
  digitalWrite(M2B, LOW);
  digitalWrite(M2A, HIGH);

  // Turn motor on 
  analogWrite(M1CTL, p + 18); //right should go slightly faster
  analogWrite(M2CTL, p); //
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
  analogWrite(M1CTL, p + 18);
  analogWrite(M2CTL, p);
  delay(ms);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0);
}

void crank90_R() {
  pivot_R(90, 900);
}

void crank90_L() {
  pivot_L(90, 900);
}

void matt_left_90() {
  // Set backward direction
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, HIGH);

  digitalWrite(M2B, HIGH);
  digitalWrite(M2A, LOW);

  analogWrite(M1CTL, 90);
  analogWrite(M2CTL, 90);
  delay(800);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0); 
}
//90, 800
void fullrotation() {
  // Set backward direction
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, HIGH);

  digitalWrite(M2B, HIGH);
  digitalWrite(M2A, LOW);

  analogWrite(M1CTL, 90);
  analogWrite(M2CTL, 90);
  delay(1600);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0); 
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

//Zinnobar = F392FC86D8D7
//Vitellary = DCF2BCAB6F0B
void postRequest(char *message) {
  Serial.print("Sending post request: ");
  Serial.println(message);
  delay(300); 
  if (client.connect(server,80)) { 
    //Serial.println("POST request");
    //this robot is F392FC86D8D7, the other robot is DCF2BCAB6F0B
    client.println("POST /F392FC86D8D7/DCF2BCAB6F0B HTTP/1.1");
    client.println("Host: ee31.ece.tufts.edu");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(strlen(message));
    client.println();
    client.print(message);
    client.println("Connection: close");
    client.println();
  }
  delay(500);
}

String getRequest() {
  if (client.connect(server,80)) {
    //this robot is F392FC86D8D7, the other robot is 4A9EDB0160D5
    client.println("GET /F392FC86D8D7/DCF2BCAB6F0B HTTP/1.1");
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
  
  delay(500); 

  //Convert messageData into a string
  String messageString = String(messageData);

  //Parse messageData. "senderID=F392FC86D8D7&receiverID=F392FC86D8D7&message=Success&MYMESSAGE.="
  int startIndex = messageString.indexOf("Success&") + 8;
  int endIndex = messageString.length() - 1;

  // Extract the substring between the start and end indexes
  String parsedMessage = messageString.substring(startIndex, endIndex);

  // Print the extracted string
  //Serial.println(parsedMessage);
  Serial.print("GET REQUEST: ");
  Serial.println(parsedMessage);
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