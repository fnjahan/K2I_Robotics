#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Servo.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Servo myServo;

const int LED_PIN = 13;          
const int THRESHOLD_DIST = 100;  // Changed to 100mm (10cm) Danger Zone

void setup() {
  Serial.begin(115200); 
  pinMode(LED_PIN, OUTPUT);      
  
  myServo.attach(9);
  myServo.write(90); 
  delay(500);

  if (!lox.begin()) {
    while (1) {
      digitalWrite(LED_PIN, HIGH); delay(100);
      digitalWrite(LED_PIN, LOW); delay(100);
    }
  }
}

void loop() {
  for (int i = 15; i <= 165; i += 2) {
    myServo.write(i);
    delay(25); 
    int distance = getDistance();
    checkProximity(distance);    
    sendData(i, distance);
  }
  for (int i = 165; i >= 15; i -= 2) {
    myServo.write(i);
    delay(25);
    int distance = getDistance();
    checkProximity(distance);    
    sendData(i, distance);
  }
}

int getDistance() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  if (measure.RangeStatus == 0) { 
    return measure.RangeMilliMeter; 
  } else {
    return 2000; 
  }
}

void checkProximity(int distance) {
  // Ignored distances under 15mm to avoid self-reflections at this wider range
  if (distance <= THRESHOLD_DIST && distance > 15) { 
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}

void sendData(int angle, int distance) {
  Serial.print(angle);
  Serial.print(",");
  Serial.println(distance); 
}