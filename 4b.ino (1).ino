char *charToBinaryString(char c);

void setup() {
  pinMode(10, OUTPUT);  // Set pin 13 as an output
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  Serial.begin(9600);  // Initialize the serial output
}

void loop() {
  char c = 'j';  // Change this to the character you want to convert
  char *binaryString = charToBinaryString(c);  // Convert the character to binary
  //Serial.println(binaryString);  // Print the binary string to the serial output
  generateOutput(binaryString);
  free(binaryString);  // Free the memory allocated for the binary string

  // // Read the output
  // readOutput();
}
char *charToBinaryString(char c) {
  char *binaryString = malloc(9 * sizeof(char));  // Allocate memory for the binary string
  int i;
  for (i = 7; i >= 0; i--) {
    if (c & (1 << i)) {  // Check if the i-th bit is 1
      binaryString[7 - i] = '1';  // If yes, add '1' to the string
    } else {
      binaryString[7 - i] = '0';  // If no, add '0' to the string
    }
  }
  binaryString[8] = '\0';  // Add a null terminator to the end of the string
  return binaryString;
}

void generateOutput(char input[]) {
  int num;
  for (int i = 0; i < 8; i++) {
    if (input[i] == '1') {
      // generate a 3kHz wave for 1/8 second
      for (int j = 0; j < 3000 / 8; j++) {
        digitalWrite(10, HIGH);
        delayMicroseconds(166);
        digitalWrite(10, LOW);
        delayMicroseconds(166);
      }
    } else {
      // output low for 1/8 second
      digitalWrite(10, LOW);
      delay(125);
    }
    // Read the output
    readOutput();
  }
}

void readOutput() {
  int num = analogRead(A5);
  Serial.print("Reading analog: ");
  Serial.print(num);
  if (num > 360) {Serial.println('1'); digitalWrite(6, HIGH);}
  else Serial.println('0');
}