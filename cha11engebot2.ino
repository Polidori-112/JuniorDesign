
#define batteryReader A0
#define R 8
#define G 9
#define BLUE_LED 11
#define GREEN_LED 11
#define RED_LED 11

int value = 0;
int brightness = 0;
float voltage;
float R2 = 1000.0;
float R1 = 2000.0;

//motor control
#define M1CTL 5
#define M1A 2
#define M1B 4

#define M2CTL 6
#define M2A 7 
#define M2B 3

//distance sensor
#define distIn A4
#define distOut 9

//color sensor
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
  digitalWrite(R_col,HIGH);
  digitalWrite(B_col,LOW);


}

void loop() {
  // backward(100, 1000);
  // delay(1000);
  // crank90_L();
  // crank90_R();
  //cena();
  delay(100);
  digitalWrite(tail, LOW);
  //Robot 1 gets request
  // followR(0);
  // //delay(1000);
  cha11enge();
  cha12enge();
  cha13enge();
  cha14enge();
  cha15enge();
  // forward(100,100);
  // digitalWrite(M1CTL, HIGH);
  // digitalWrite(M2CTL, LOW);
  // digitalWrite(M1A, HIGH);
  // digitalWrite(M1B, LOW);
  // digitalWrite(M2A, HIGH);
  // digitalWrite(M2B, LOW);
  // digitalWrite(12, HIGH);
  // digitalWrite(13, LOW);
  // digitalWrite(12, HIGH);
  // digitalWrite(13, LOW);
  Serial.println(analogRead(col));
  //delay(100000);

}
void cha11enge() {
  int c;
  //down, back
   while (1) {
    forward(100, 100);
     if (analogRead(distIn) < 100) {
       crank90_R();
       crank90_R();
       break;
     }
   }
  while(1) {
    digitalWrite(B_col,LOW);
    forward(100, 100);
    c = analogRead(col);
    if (c < 630) {
      //digitalWrite(B_col,HIGH);
      // crank90_L();
      // crank90_L();
      forward(100, 400);
      //delay(500);
      digitalWrite(B_col,HIGH);
      followL(0);
      break;
    }
  }
  pivot_R(77, 1000);
  digitalWrite(B_col,LOW);
  followL(0);
  crank90_R();
  forward(100, 1200);
  crank90_R();
  crank90_R();
  forward(100, 2000);
  delay(2000);
  backward(100, 2500);


}
void cha12enge() {
  
  //COMM ITEM HERE
  
  forward(100, 100);
  backward(100, 100);
  digitalWrite(B_col,HIGH);
  followR(0);
  digitalWrite(B_col,LOW);
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
  crank90_R();
  delay(500);
  pivot_R(100, 400);
  forward(100, 800);
  
  cena();
  digitalWrite(G, LOW);
  digitalWrite(tail, HIGH);  
  followL(0);
}
void cha14enge() {
  crank90_R();
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

  cena();
  delay(500);

  cena();

}


void cena() {
  // generate a square wave at 49Hz for 0.25 seconds
  for (int i = 0; i < 122; i++) {
    digitalWrite(horn, HIGH);
    delayMicroseconds(1020);
    digitalWrite(horn, LOW);
    delayMicroseconds(1020);
  }

  // generate a square wave at 61.74Hz for 0.125 seconds
  for (int i = 0; i < 61; i++) {
    digitalWrite(horn, HIGH);
    delayMicroseconds(810);
    digitalWrite(horn, LOW);
    delayMicroseconds(810);
  }

  // generate a square wave at 43.65Hz for 0.125 seconds
  for (int i = 0; i < 61; i++) {
    digitalWrite(horn, HIGH);
    delayMicroseconds(1146);
    digitalWrite(horn, LOW);
    delayMicroseconds(1146);
  }

  // generate a silence for 0.125 seconds
  delay(125);

  // generate a square wave at 49Hz for 1 second
  for (int i = 0; i < 490; i++) {
    digitalWrite(horn, HIGH);
    delayMicroseconds(1020);
    digitalWrite(horn, LOW);
    delayMicroseconds(1020);
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
  //nt time_now = millis();
  // //perform all checks in this loop
  // while (millis() < (time_now + d)) {
  //   //if analogRead((distIn < 100)) return;
  //     if (analogRead(distIn) > 100)
  //     digitalWrite(distOut, LOW);
  // else {
  //   digitalWrite(distOut, HIGH);
  //   stop();
  //   return;}

  // }


  // }
  // return;
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
  analogWrite(M2CTL, p + 35);
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
  analogWrite(M1CTL, p + 18);
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
  analogWrite(M1CTL, p + 18);
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
