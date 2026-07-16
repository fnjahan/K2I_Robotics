#include <Servo.h>

Servo doorServo;
const int irPin = 2;       // IR sensor signal connected to pin 2
const int servoPin = 9;    // Servo signal connected to pin 9

void setup() {
  doorServo.attach(servoPin);
  pinMode(irPin, INPUT_PULLUP); // Use internal pull-up resistor
  
  // Start with the shield in its original position
  doorServo.write(90); 
}

void loop() {
  int beamState = digitalRead(irPin);

  if (beamState == LOW) { // LOW means the beam is broken (debris detected)
    doorServo.write(0);  // Deploy the Shield(rotate servo to 0 degrees)
    delay(3000);          // Wait for 3 seconds
  } else {
    doorServo.write(90);   // Close shield to original position (rotate servo back to 90 degrees)
  }

  delay(100); // Small delay to prevent system overload
}

