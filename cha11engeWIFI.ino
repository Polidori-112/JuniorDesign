// This is vitabot
#define SECRET_SSID "junior"
#define SECRET_PASS "designdesign"

#define batteryReader A0
#define R 8
#define G 9

#define RED_LED 8
#define GREEN_LED 9
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
#define distOut 9

#define B_col 13
#define R_col 12
#define col A5

#define com_in A3
#define com_out 10

#define light_thresh 100

#define tail 0
#define head 1
#define horn 11

struct color {int val; int mag;};

unsigned long time_now;

#include <SPI.h>
#include <WiFiNINA.h>
//#include "arduino_secrets.h" 
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

  // //Robot sends commands
  sendCommands();

  // //Robot gets commands
  getAllCommands();
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
  Serial.println("Sending command 1: phase 1");
  postRequest("ONE ");
  waitFor("BUSY");

  Serial.println("Sending command 2: phase 2");
  postRequest("TWO ");
  waitFor("BUSY");

  Serial.println("Sending command 3: phase 3");
  postRequest("THREE ");
  waitFor("BUSY");

  Serial.println("Sending command 2: phase 4");
  postRequest("FOUR ");
  waitFor("BUSY");

  Serial.println("Sending command 3: phase 5");
  postRequest("FIVE ");
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
  String outputWord;

  // Extract the action and number
  int spaceIndex = getReq.indexOf(' ');
  String action = getReq.substring(0, spaceIndex);

  Serial.print("Executing action: ");
  Serial.print(action);

  postRequest("BUSY");
  if (action == "ONE ") {
    cha11enge();
  }
  else if (action == "TWO ") {
    cha12enge();
  }
  else if (action == "THREE ") {
    cha13enge();
  }
  else if (action == "FOUR ") {
    cha14enge();
  }
  else if (action == "FIVE ") {
    cha15enge();
  }
  else {
    stop();
  }
  //Stop before next command
  stop();
}

// void movement_calibration() {
//   //Forward inches
//   forward(100, 2200);
//   delay(1000);

//   //Full rotation
//   fullrotation();
//   delay(1000);

//   // //Backwards
//   backward(100, 600);
//   delay(1000);

//   //Turn left
//   crank90_L();
//   delay(1000);

//   // Move a lil bit?
//   forward(100, 500);
//   delay(1000);

//   //Turn Right
//   crank90_R();
//   delay(1000);

//   //forwards 15
//   forward(100, 2000);
//   delay(1000);

//   //Turn Right
//   crank90_R();
//   delay(1000);
//   //Turn Right
//   crank90_R();
//   delay(1000);

//   //Backwards a lil bit
//   backward(100, 600);
//   delay(1000);
// }

void cha11enge() {
  int c;
  //down, back
  // while (1) {
  //  forward(100, 100);
  //   if (analogRead(distIn) < 100) {
  //     crank90_R();
  //     crank90_R();
  //     break;
  //   }
  // }
  while(1) {
    digitalWrite(B_col,LOW);
    forward(100, 100);
    c = analogRead(col);
    if (c < 620) {
      //digitalWrite(B_col,HIGH);
      // crank90_L();
      // crank90_L();
      forward(100, 400);
      delay(500);
      followR(0);
      break;
    }
  }
  pivot_L(77, 1100);
  followR(0);
  crank90_L();
  forward(100, 1200);



}
void cha12enge() {
  
  //COMM ITEM HERE
  crank90_L();
  crank90_L();
  forward(100, 100);
  backward(100, 100);
  followL(0);
  digitalWrite(R_col, HIGH);
  delay(250);
  digitalWrite(R_col, HIGH);
  delay(250);
}
void cha13enge() {
  //COMM ITEM HERE

  digitalWrite(R, HIGH);
  delay(250);
  digitalWrite(R, LOW);
  delay(250);
  digitalWrite(R, HIGH);
  delay(250);
  digitalWrite(R, LOW);
  delay(250);
  digitalWrite(R, HIGH);
  delay(250);
  digitalWrite(R, LOW);
  delay(250);
  digitalWrite(G, HIGH);

  backward(100, 500);
  crank90_L();
  delay(500);
  pivot_L(100, 400);
  forward(100, 800);
  
  for (int i = 0; i < 1000; i++) {
    digitalWrite(horn, LOW);
    delay(1);
    digitalWrite(horn, HIGH);
    delay(1);
  }  
  digitalWrite(G, LOW);
  digitalWrite(tail, HIGH);  
  followR(0);
}
void cha14enge() {
  crank90_L();
  forward(100, 1200);
}
void cha15enge() {
  digitalWrite(R, HIGH);
  digitalWrite(tail, HIGH);
  digitalWrite(head, HIGH);
  digitalWrite(G, HIGH);
  delay(250);
  digitalWrite(R, LOW);
  digitalWrite(tail, LOW);
  digitalWrite(head, LOW);
  digitalWrite(G, LOW);
  delay(250);
  digitalWrite(R, HIGH);
  digitalWrite(tail, HIGH);
  digitalWrite(head, HIGH);
  digitalWrite(G, HIGH);
  delay(250);
  digitalWrite(R, LOW);
  digitalWrite(tail, LOW);
  digitalWrite(head, LOW);
  digitalWrite(G, LOW);
  delay(250);  
  digitalWrite(R, HIGH);
  digitalWrite(tail, HIGH);
  digitalWrite(head, HIGH);
  digitalWrite(G, HIGH);
  delay(250);
  digitalWrite(R, LOW);
  digitalWrite(tail, LOW);
  digitalWrite(head, LOW);
  digitalWrite(G, LOW);
  delay(250);

    for (int i = 0; i < 500; i++) {
    digitalWrite(horn, LOW);
    delay(1);
    digitalWrite(horn, HIGH);
    delay(1);
  }  
  delay(500);

    for (int i = 0; i < 500; i++) {
    digitalWrite(horn, LOW);
    delay(1);
    digitalWrite(horn, HIGH);
    delay(1);
  }  
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

void delayCheck(int d) {
  delay(d);
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


void followR(int val) {
  int reference;
  int curr;
  // digitalWrite(B_col, HIGH);
  // digitalWrite(R_col, HIGH);
  delayCheck(100); 
  if (!val)
    reference = analogRead(col);
  else
    reference = val;
  curr = 0;
  int x = reference;

  while (1) {
    x = fR(x);
    if (x > 1500)
      break;
  }

}
int fR(int x) {
  int curr = 0;
  int reference = x;
    while (curr < 20 && curr > -20) {
    //skkkrrrrrrrrtttt a little to the right
    forwardR(100, 100);
    curr = reference - analogRead(col);;  
      if (analogRead(distIn) < 100) return 2000;
  }
  reference = analogRead(col);
  curr = 0;
  while (curr < 10 && curr > -10) {
    pivot_L(80, 70);
    curr = reference - analogRead(col);;
    if (analogRead(distIn) < 100) return 2000;
  }  
  return x;
}
void followL(int val) {
  int reference;
  int curr;
  // digitalWrite(B_col, HIGH);
  // digitalWrite(R_col, HIGH);
  delayCheck(100); 
  if (!val)
    reference = analogRead(col);
  else
    reference = val;
  curr = 0;
  int x = reference;
  while (1) {
    x = fL(x);
    if (x > 1500)
      break;
  }

  
}
int fL(int x) {
  int curr = 0;
    int reference = x;
  while (curr < 20 && curr > -20) {
    //skkkrrrrrrrrtttt a little to the right
    forwardL(100, 100);
    curr = reference - analogRead(col);;  
      if (analogRead(distIn) < 100) return 2000;
  }
  reference = analogRead(col);
  curr = 0;
  while (curr < 10 && curr > -10) {
    pivot_R(80, 70);
    curr = reference - analogRead(col);;
    if (analogRead(distIn) < 100) return 2000;
  }
  return x;
}

//p is out of 255
void forwardR(int p, int ms) {
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

void forwardL(int p, int ms) {
  // Set forward direction
  digitalWrite(M1B, LOW);
  digitalWrite(M1A, HIGH);
  digitalWrite(M2B, LOW);
  digitalWrite(M2A, HIGH);

  // Turn motor on 
  analogWrite(M1CTL, p + 55);
  analogWrite(M2CTL, p);
  delayCheck(ms);
  analogWrite(M1CTL, 0);
  analogWrite(M2CTL, 0);
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
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(B_col, OUTPUT);
  pinMode(R_col, OUTPUT);
  pinMode(horn, OUTPUT);
  
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M1CTL, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M2CTL, OUTPUT);
  pinMode(tail, OUTPUT);
  digitalWrite(M1CTL, LOW);
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2CTL, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);
  digitalWrite(R_col, HIGH);
  digitalWrite(B_col, HIGH);

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
