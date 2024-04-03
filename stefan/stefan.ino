#include <LedControl.h>

const int DIN_PIN = 13;
const int CS_PIN = 11;
const int CLK_PIN = 12;

const uint64_t IMAGE = 0x3c4295a1a195423c;

LedControl display = LedControl(DIN_PIN, CLK_PIN, CS_PIN);

#define TRIG_PIN 9
#define ECHO_PIN 10
#define PIR_PIN 2

long duration, distance; // variables for ultrasonic sensor
int pirState = LOW; // variable to store the PIR sensor state

void setup() {
  Serial.begin(9600);
  display.clearDisplay(0);
  display.shutdown(0, false);
  display.setIntensity(0, 1);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
}

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      display.setLed(0, i, j, bitRead(row, j));
    }
  }
}

void loop() {
  // Read the PIR sensor state
  pirState = digitalRead(PIR_PIN);

  // Ultrasonic sensor detection
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // Check if either sensor detects an obstacle
  if (pirState == HIGH) {
    Serial.println("PIR sensor detected an obstacle");
    displayImage(IMAGE); // Display the image
    delay(1200);
    display.clearDisplay(0);
    delay(100); // Delay between sensor detection and image display
  } else if (distance < 30 && distance > 0) {
    Serial.println("Ultrasonic sensor detected an obstacle");
    displayImage(IMAGE); // Display the image
    delay(1200);
    display.clearDisplay(0);
    delay(100); // Delay between sensor detection and image display
  } else {
    Serial.println("No obstacle detected");
    delay(100); // Adjust delay time if needed
  }
}
