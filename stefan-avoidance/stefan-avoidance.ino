#include <Servo.h>

const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor1Enable = 9;

const int motor2Pin1 = 4;
const int motor2Pin2 = 5;
const int motor2Enable = 10;

const int servoPin = 6;
const int trigPin = 7;
const int echoPin = 8;

const int distanceThreshold = 30; // in cm

const int motorSpeed = 255; // full throttle

Servo myServo;

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1Enable, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Enable, OUTPUT);
  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.write(90); // center servo
  delay(1000);
}

void loop() {
  myServo.write(90);
  delay(500);
  long distance = measureDistance();
  if (distance < distanceThreshold) {
    avoidObstacle();
  } else {
    moveForward();
  }
  delay(100);
}

long measureDistance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void moveForward() {
  Serial.println("Moving forward");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(motor1Enable, motorSpeed);  
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(motor2Enable, motorSpeed); 
}

void stopMotors() {
  Serial.println("Stopping motors");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(motor1Enable, 0);  
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(motor2Enable, 0);  
}

void moveBackward() {
  Serial.println("Moving backward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  analogWrite(motor1Enable, motorSpeed);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(motor2Enable, motorSpeed);
  delay(500); // move backward for 0.5 second
  stopMotors();
  delay(250);
}

void turnLeft() {
  Serial.println("Turning left");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  analogWrite(motor1Enable, motorSpeed);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(motor2Enable, motorSpeed);
  delay(150);  // turn for 0.15 second
  stopMotors();
  delay(250);
}

void turnRight() {
  Serial.println("Turning right");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  analogWrite(motor1Enable, motorSpeed);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(motor2Enable, motorSpeed);
  delay(150);  // turn for 0.15 second
  stopMotors();
  delay(250);
}

void avoidObstacle() {
  stopMotors();
  delay(500); 
  moveBackward();
  delay(500); // move backward for 0.5 second
  stopMotors();
  delay(500);

  // check sorroundings
  long leftDistance, rightDistance;
  myServo.write(0);
  delay(1000);
  leftDistance = measureDistance();
  myServo.write(180);
  delay(1000); 
  rightDistance = measureDistance();
  myServo.write(90); 
  delay(500); 

  // decide where to go
  if (leftDistance > rightDistance) {
    turnLeft();
  } else {
    turnRight();
  }
  delay(250);
  moveForward();
}
