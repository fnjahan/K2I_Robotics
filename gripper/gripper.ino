#include <Servo.h>

Servo gripperServo;
const int buttonClosePin = 2; 
const int buttonOpenPin = 3;  
const int servoPin = 9;       

// Adjustable angles. Change these if your gripper jams or buzzes.
const int CLOSE_ANGLE = 0;  // Closes the gripper
const int OPEN_ANGLE = 90;    // Opens the gripper

void setup() {
  gripperServo.attach(servoPin);
  pinMode(buttonClosePin, INPUT_PULLUP); 
  pinMode(buttonOpenPin, INPUT_PULLUP);  
  
  // Set initial position to open
  gripperServo.write(OPEN_ANGLE);
}

void loop() {
  // Press Button 1 to close
  if (digitalRead(buttonClosePin) == LOW) {
    gripperServo.write(CLOSE_ANGLE);
    delay(250); 
  }
  
  // Press Button 2 to open
  if (digitalRead(buttonOpenPin) == LOW) {
    gripperServo.write(OPEN_ANGLE);
    delay(250); 
  }
}
