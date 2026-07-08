#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Adafruit_VL53L0X.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lox.begin();
  lox.startRange();
}

void loop() {
  uint16_t distanceMm = lox.readRange(); 
  int distanceCm = distanceMm / 10;

  lcd.clear();
  lcd.setCursor(0, 0);

  if (distanceCm > 150) {
    lcd.print("Out of Range");
    setColor(0, 0, 255); 
  } 
  else {
    lcd.print("Dist: ");
    lcd.print(distanceCm);
    lcd.print(" cm");

    if (distanceCm <= 10) {
      setColor(255, 0, 0); 
    } 
    else if (distanceCm <= 30) {
      setColor(255, 150, 0); 
    } 
    else {
      setColor(0, 255, 0); 
    }
  }
  delay(150); 
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
