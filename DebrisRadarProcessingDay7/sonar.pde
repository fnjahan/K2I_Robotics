import processing.serial.*;

Serial myPort;
int angle = 15;
int distance = 2000;
int maxDistance = 100; // Zoomed to 10cm max scale
String rawBuffer = ""; 

void setup() {
  size(1200, 700);
  smooth();
  String portName = Serial.list()[2]; // Lock onto your Mac's Arduino port
  myPort = new Serial(this, portName, 115200); 
  background(0);
}

void draw() {
  while (myPort.available() > 0) {
    char inChar = myPort.readChar();
    if (inChar == '\n') { 
      rawBuffer = trim(rawBuffer);
      int[] values = int(split(rawBuffer, ','));
      if (values != null && values.length == 2) {
        angle = values[0];
        distance = values[1];
      }
      rawBuffer = ""; 
    } else if (inChar != '\r') {
      rawBuffer += inChar; 
    }
  }

  noStroke();
  fill(0, 15); 
  rect(0, 0, width, height);
  
  pushMatrix();
  translate(width/2, height - 50);
  
  float maxRadius = width/2 - 50;
  
  // --- NEW: DANGER ZONE OVERLAY ---
  // Map 20mm (2cm) to pixel radius size based on our 100mm max scale
  float dangerRadius = map(20, 0, maxDistance, 0, maxRadius);
  
  if (distance <= 20 && distance > 5) {
    // Flash transparent red overlay when an object is inside 2cm
    fill(255, 0, 0, 40 + sin(frameCount * 0.2) * 20); 
    stroke(255, 0, 0, 150);
    strokeWeight(2);
  } else {
    // Static faint red boundary arc when clear
    noFill();
    stroke(255, 0, 0, 50); 
    strokeWeight(1);
  }
  // Draw the 2cm boundary arc zone
  arc(0, 0, dangerRadius * 2, dangerRadius * 2, PI, TWO_PI);
  
  // Draw regular grid circles
  noFill();
  strokeWeight(1);
  stroke(0, 150, 0);
  for (int i = 1; i <= 4; i++) {
    float r = (maxRadius / 4.0) * i;
    arc(0, 0, r*2, r*2, PI, TWO_PI);
  }
  
  // Sweep line
  float rad = radians(angle);
  strokeWeight(3);
  stroke(0, 255, 0);
  line(0, 0, maxRadius * cos(PI + rad), maxRadius * sin(PI + rad));
  
  // Targets Blip
  if (distance < maxDistance) {
    float displayDist = map(distance, 0, maxDistance, 0, maxRadius);
    if (distance <= 20) {
      strokeWeight(16); // Double sized blip for critical danger
      stroke(255, 0, 0); 
    } else {
      //strokeWeight(8);
      //stroke(0, 150, 255);
      strokeWeight(16); // Double sized blip for critical danger
      stroke(255, 0, 0);
    }
    point(displayDist * cos(PI + rad), displayDist * sin(PI + rad));
  }
  popMatrix();
  
  // Telemetry Text Text Display
  fill(0); noStroke(); rect(10, 10, 250, 75);
  fill(0, 255, 0); textSize(16);
  text("Angle: " + angle + "°", 20, 30);
  text("Distance: " + distance + " mm", 20, 50);
  if (distance <= 20 && distance > 5) {
    fill(255, 0, 0);
    text("DANGER: OBJECT IN 2CM RANGE!", 20, 70);
  }
}
