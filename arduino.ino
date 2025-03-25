// Pins for 10 shift registers on a Mega
const int dataPins[10] = {22, 24, 26, 28, 30, 44, 46, 48, 50, 52}; // Example pin assignments
const int latchPins[10] = {2, 3, 4, 5, 6, A15, A14, A13, A12, A11}; // Example pin assignments
const int clockPins[10] = {9, 10, 11, 12, 13, A7, A6, A5, A4, A3}; // Example pin assignments


// Define segment patterns for 0-9, adjusted for Q1-Q7 (7 LEDs)
const byte segments[10] = {
  B01111110, // 0 (Q2-Q7 on, Q1 and Q8 off)
  B00110000, // 1 (Q3-Q4 on)
  B01101101, // 2
  B01111001, // 3
  B00110011, // 4
  B01011011, // 5
  B01011111, // 6
  B01110000, // 7
  B01111111, // 8
  B01110011  // 9
};

void setup() {
  // All pins are outputs
  for (int i = 0; i < 10; i++) {
    pinMode(latchPins[i], OUTPUT);
    pinMode(dataPins[i], OUTPUT);
    pinMode(clockPins[i], OUTPUT);
  }

  // Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Test each LED on each shift register (Q1-Q7)
  for (int registerNum = 0; registerNum < 10; registerNum++) {
    for (int ledNum = 0; ledNum < 7; ledNum++) { // Iterate Q1-Q7
      byte ledPattern = 1 << (ledNum + 1); // Create a pattern with only one LED on (Q1 is bit 0, so Q2 is bit 1)

      digitalWrite(latchPins[registerNum], LOW);
      shiftOut(dataPins[registerNum], clockPins[registerNum], MSBFIRST, ledPattern);
      digitalWrite(latchPins[registerNum], HIGH);

      Serial.print("Register: ");
      Serial.print(registerNum);
      Serial.print(", LED: ");
      Serial.println(ledNum + 2); // LED numbers are Q2-Q8, so add 2

      delay(2000); // Display each LED for 0.5 seconds
    }
  }

  // Test all segments for all registers.
  for (int registerNum = 0; registerNum < 10; registerNum++) {
    for (int segmentPatternIndex = 0; segmentPatternIndex < 10; segmentPatternIndex++) {
      digitalWrite(latchPins[registerNum], LOW);
      shiftOut(dataPins[registerNum], clockPins[registerNum], MSBFIRST, segments[segmentPatternIndex]);
      digitalWrite(latchPins[registerNum], HIGH);

      Serial.print("Register: ");
      Serial.print(registerNum);
      Serial.print(", Segment pattern: ");
      Serial.println(segmentPatternIndex);

      delay(2000);
    }
  }
}