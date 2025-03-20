int inByte = '0';

void setup() {

  Serial.begin(9600);

  pinMode(12, OUTPUT);

}

void loop() {

  if (Serial.available() > 0) {

    inByte = (Serial.read());

    Serial.print("inByte "); Serial.println(inByte);

    if (inByte == '1') {

      digitalWrite(12, HIGH);

    }

    if (inByte == '0') {

      digitalWrite(12, LOW);

    }

  }

}