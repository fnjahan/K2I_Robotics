#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 or 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int fsrPin = A0; 

// Individual pins for the 5 LEDs
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int led5 = 6;

void setup() {
  // Initialize the LCD
  lcd.init();                      
  lcd.backlight(); // Turn on the blacklight
  
  // Print static text on top row
  lcd.setCursor(0, 0);
  lcd.print("Force Value:");
  
  // Set LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void loop() {
  int sensorReading = analogRead(fsrPin);
  
  // --- Display live value on second row ---
  lcd.setCursor(0, 1);
  lcd.print(sensorReading);
  lcd.print(" "); // Spaces overwrite old numbers when values drop
  
  // --- LED Logic via If Statements ---
  // LED 1
  if (sensorReading > 100) { digitalWrite(led1, HIGH); } 
  else { digitalWrite(led1, LOW); }
  
  // LED 2
  if (sensorReading > 300) { digitalWrite(led2, HIGH); } 
  else { digitalWrite(led2, LOW); }
  
  // LED 3
  if (sensorReading > 500) { digitalWrite(led3, HIGH); } 
  else { digitalWrite(led3, LOW); }
  
  // LED 4
  if (sensorReading > 700) { digitalWrite(led4, HIGH); } 
  else { digitalWrite(led4, LOW); }
  
  // LED 5
  if (sensorReading > 900) { digitalWrite(led5, HIGH); } 
  else { digitalWrite(led5, LOW); }
  
  delay(100); // Prevents screen flickering
}
