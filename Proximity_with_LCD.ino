#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define Ultrasonic sensor pins
const int trigPin = 4;
const int echoPin = 5;

// Variables for duration and distance
long duration;
int distanceCm;

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Clear the trigPin by setting it LOW for a brief moment
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor by setting the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returning the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  // Speed of sound is 340 m/s or 29 microseconds per centimeter
  distanceCm = duration * 0.034 / 2;
  
  // Print the distance to the LCD
  lcd.clear(); // Clears previous display characters
  lcd.setCursor(0, 0); // Set cursor to column 0, line 0
  lcd.print("Distance: ");
  lcd.print(distanceCm);
  lcd.print(" cm");
  
  // Wait a short time before the next measurement
  delay(500);
}