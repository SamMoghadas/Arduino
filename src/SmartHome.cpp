// Smart Home System using Arduino
// Controls lights, fan, and security system based on sensor inputs

// Pin Definitions
const int lightSensorPin = A0;    // LDR sensor for light intensity
const int motionSensorPin = 2;    // PIR sensor for motion detection
const int tempSensorPin = A1;     // LM35 temperature sensor
const int lightPin = 9;           // LED for light control (PWM)
const int fanPin = 10;            // Fan control (PWM)
const int buzzerPin = 8;          // Buzzer for security alarm

// Thresholds
const int lightThreshold = 500;   // Light intensity threshold for turning on lights
const int tempThreshold = 30;     // Temperature threshold for turning on the fan
const unsigned long alarmDuration = 5000; // Duration for the alarm to sound (in milliseconds)

// Variables
int lightIntensity = 0;
int temperature = 0;
bool motionDetected = false;
unsigned long alarmStartTime = 0;
bool alarmActive = false;

void setup() {
  // Initialize pins
  pinMode(lightSensorPin, INPUT);
  pinMode(motionSensorPin, INPUT);
  pinMode(tempSensorPin, INPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Start serial communication for debugging
  Serial.begin(9600);
  Serial.println("Smart Home System Initialized!");
}

void loop() {
  // Read sensor values
  lightIntensity = analogRead(lightSensorPin);
  temperature = readTemperature();
  motionDetected = digitalRead(motionSensorPin);

  // Control lights based on light intensity
  if (lightIntensity < lightThreshold) {
    analogWrite(lightPin, 255); // Turn on lights at full brightness
  } else {
    analogWrite(lightPin, 0); // Turn off lights
  }

  // Control fan based on temperature
  if (temperature > tempThreshold) {
    analogWrite(fanPin, 255); // Turn on fan at full speed
  } else {
    analogWrite(fanPin, 0); // Turn off fan
  }

  // Security system: Activate alarm if motion is detected
  if (motionDetected && !alarmActive) {
    alarmActive = true;
    alarmStartTime = millis();
    Serial.println("Motion detected! Alarm activated.");
  }

  // Handle alarm
  if (alarmActive) {
    digitalWrite(buzzerPin, HIGH); // Sound the buzzer
    if (millis() - alarmStartTime >= alarmDuration) {
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
      alarmActive = false;
      Serial.println("Alarm deactivated.");
    }
  }

  // Print sensor values to serial monitor for debugging
  Serial.print("Light Intensity: ");
  Serial.print(lightIntensity);
  Serial.print(" | Temperature: ");
  Serial.print(temperature);
  Serial.print("°C | Motion Detected: ");
  Serial.println(motionDetected ? "Yes" : "No");

  // Small delay to stabilize readings
  delay(500);
}

// Function to read temperature from LM35 sensor
int readTemperature() {
  int tempValue = analogRead(tempSensorPin);
  float voltage = tempValue * (5.0 / 1023.0);
  float tempC = voltage * 100; // Convert voltage to temperature in Celsius
  return static_cast<int>(tempC);
}
