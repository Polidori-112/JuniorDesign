const int sensorPin = A5; // Pin connected to the light sensor
unsigned long signalStartTime = 0; // Time when the signal starts
int signalDuration = 0; // Duration of the signal
int signalThreshold = 360; // Threshold for detecting the signal
String binaryString = ""; // Binary string to store the received data
int bitCount = 0; // Count of bits received
char receivedChar; // Character received from the binary string

void setup() {
  Serial.begin(9600); // Initialize the serial output
  pinMode(sensorPin, INPUT); // Set the light sensor pin as input
}

void loop() {
  int num = analogRead(sensorPin);
  // Wait for the signal to start
  // while (analogRead(num) > signalThreshold);
  // //Serial.println("Starting");
  // signalStartTime = millis();

  // // Wait for the signal to end
  // while (analogRead(sensorPin) < signalThreshold);
  // //Serial.println("Ending");
  // signalDuration = millis() - signalStartTime;

  // Serial.print("Signal duration: ");
  // Serial.println(signalDuration);

  if (num > 360) {
    Serial.println('1'); 
    binaryString += "1";
    bitCount++;
  }
  else {
    Serial.println('0');
    binaryString += "0";
    bitCount++;
  }

  Serial.println(bitCount);

  // Check if we have received 8 bits
  if (bitCount == 8) {
    receivedChar = strtol(binaryString.c_str(), 0, 2); // Convert the binary string to a character
    Serial.print("Received character: ");
    Serial.print(receivedChar);
    Serial.print(binaryString);
    binaryString = "";
    bitCount = 0;
  }
}