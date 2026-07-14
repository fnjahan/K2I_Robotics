// Define Pin Allocations
const int SENSOR_PIN = 2; // Row 11: Heschen Proximity Sensor Input
const int LED_PIN = 13;   // Row 20: Breadboard LED Output
const int MAGNET_PIN = 3; // Keyestudio 'S' (Signal) Pin Input

void setup() {
  pinMode(SENSOR_PIN, INPUT);   // Read sensor state
  pinMode(LED_PIN, OUTPUT);      // Drive LED indicator
  pinMode(MAGNET_PIN, OUTPUT);   // Control Keyestudio Electromagnet
  
  Serial.begin(9600);         
  Serial.println("System Online: Proximity Triggered Magnet Ready.");
}

void loop() {
  int sensorState = digitalRead(SENSOR_PIN); 

  // For Heschen NPN NO Sensors: LOW means metal is detected
  if (sensorState == LOW) {
    digitalWrite(LED_PIN, HIGH);       // Turn on breadboard LED
    digitalWrite(MAGNET_PIN, HIGH);    // Activate Keyestudio Electromagnet
    Serial.println("[!] METAL DETECTED - ELECTROMAGNET ON"); 
  } else {
    digitalWrite(LED_PIN, LOW);        // Turn off breadboard LED
    digitalWrite(MAGNET_PIN, LOW);     // Deactivate Keyestudio Electromagnet
    Serial.println("Searching... Electromagnet Off.");
  }
  
  delay(100); // 100ms reading stability delay
}
