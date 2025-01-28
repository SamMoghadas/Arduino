void setup() {
  Serial.begin(9600);

  for (int pin = 2; pin <= 13; pin++) {
    pinMode(pin, INPUT);
  }
  for (int pin = A0; pin <= A5; pin++) {
    pinMode(pin, INPUT);
  }

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  for (int pin = 2; pin <= 13; pin++) {
    int value = digitalRead(pin);
    Serial.print("Digital Pin ");
    Serial.print(pin);
    Serial.print(": ");
    Serial.println(value == HIGH ? "HIGH" : "LOW");
  }

  for (int pin = A0; pin <= A5; pin++) {
    int value = analogRead(pin);
    Serial.print("Analog Pin ");
    Serial.print(pin);
    Serial.print(": ");
    Serial.println(value);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  Serial.println("Test completed");
  delay(5000);
}
