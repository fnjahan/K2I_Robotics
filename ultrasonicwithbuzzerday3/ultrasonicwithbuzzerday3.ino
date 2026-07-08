#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with address 0x27, 16 chars, and 2 lines
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  lcd.init(); // Initialize LCD
  lcd.backlight(); // Turn on backlight
}

void loop() {
  long duration;
  int distance;
  
  // Send 10us pulse to trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo pin and calculate distance in cm
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  // Display distance on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");
  
  // Buzzer Beep Logic
  if (distance <= 10 && distance > 0) {
    // Under 10 cm: Beep fast
    digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(buzzerPin, LOW);
    delay(50);
  } 
  else if (distance > 10 && distance <= 20) {
    // 10-20 cm: Beep medium-fast
    digitalWrite(buzzerPin, HIGH);
    delay(150);
    digitalWrite(buzzerPin, LOW);
    delay(150);
  } 
  else if (distance > 20 && distance <= 30) {
    // 20-30 cm: Beep slow
    digitalWrite(buzzerPin, HIGH);
    delay(300);
    digitalWrite(buzzerPin, LOW);
    delay(300);
  } 
  else if (distance > 30 && distance <= 40) {
    // 30-40 cm: Beep very slow
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  } 
  else {
    // Over 40 cm: Buzzer is silent
    digitalWrite(buzzerPin, LOW);
    delay(100); // Wait briefly before the next check
  }
}
