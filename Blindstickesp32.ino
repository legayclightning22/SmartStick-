#include <BluetoothSerial.h>
#include <Ultrasonic.h>

BluetoothSerial btSerial;
Ultrasonic ultrasonic(4, 5);  // Trig pin: 4, Echo pin: 5

String detectedObject = "";
long distance = 0;

void setup() {
  Serial.begin(115200);  // For communication with ESP32-CAM
  btSerial.begin("ESP32_BlindStick");  // Bluetooth pairing

  Serial.println("ESP32 initialized.");
}

void loop() {
  // 1. Check for object detection data from ESP32-CAM
  if (Serial.available()) {
    detectedObject = Serial.readStringUntil('\n');
    Serial.println("Detected object: " + detectedObject);
  }

  // 2. Get distance from the ultrasonic sensor
  distance = ultrasonic.read();

  // 3. Provide feedback via Bluetooth based on object detection and distance
  if (distance < 100) {  // If distance is less than 1 meter
    String feedback = "Obstacle " + String(distance) + " cm ahead. Detected: " + detectedObject;
    btSerial.println(feedback);  // Send feedback to Bluetooth headphones
  }

  delay(1000);  // Adjust delay as needed
}
