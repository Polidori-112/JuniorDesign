/*
 This example connects to an unencrypted WiFi network.
 Then it prints the MAC address of the WiFi module,
 the IP address obtained, and other network details.

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */
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
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
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

void loop() {
  // check the network connection once every 10 seconds:
  //delay(10000);
  //printCurrentNet();

  //Robot sends hi
  postRequest("hello robot 2");
  delay(5000);

  //Robot asks to blink
  postRequest("BLINK");
  delay(5000);

  String message = getRequest();
  Serial.println(message);
}

//F392FC86D8D7
void postRequest(char *message) {
  Serial.print("Sending post request: ");
  Serial.println(message);
  Serial.println("");
  delay(300); 
  if (client.connect(server,80)) { 
    //Serial.println("POST request");
    //this robot is 4A9EDB0160D5, the other robot is F392FC86D8D7
    client.println("POST /4A9EDB0160D5/F392FC86D8D7 HTTP/1.1");
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
    //this robot is 4A9EDB0160D5, the other robot is F392FC86D8D7
    client.println("GET /4A9EDB0160D5/F392FC86D8D7 HTTP/1.1");
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
  
  delay(5000); 

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
