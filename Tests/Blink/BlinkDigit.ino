
// Pins for 10 shift registers on a Mega
const int latchPins[10] = {2, 3, 4, 5, 6, A15, A14, A13, A12, A11}; // Example pin assignments
const int dataPins[10] = {22, 24, 26, 28, 30, 44, 46, 48, 50, 52}; // Example pin assignments
const int clockPins[10] = {9, 10, 11, 12, 13, A7, A6, A5, A4, A3}; // Example pin assignments

int time = 200;

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
  // Blink each register individually
  for (int registerNum = 0; registerNum < 10; registerNum++) {
    // Turn on current registerz
    digitalWrite(latchPins[registerNum], LOW);
    shiftOut(dataPins[registerNum], clockPins[registerNum], MSBFIRST, B11111111); // Turn all LEDs on
    digitalWrite(latchPins[registerNum], HIGH);

    Serial.print("Register: ");
    Serial.print(registerNum);
    Serial.println(" ON");

    delay(time); // Wait for 1 second

    // Turn off current register
    digitalWrite(latchPins[registerNum], LOW);
    shiftOut(dataPins[registerNum], clockPins[registerNum], MSBFIRST, B00000000); // Turn all LEDs off
    digitalWrite(latchPins[registerNum], HIGH);

    Serial.print("Register: ");
    Serial.print(registerNum);
    Serial.println(" OFF");

    delay(time); // Wait for 0.5 second
  }
}