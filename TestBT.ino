#include <BluetoothSerial.h>  // Include BluetoothSerial library

BluetoothSerial btSerial;

void setup() {
  Serial.begin(115200);  // Debugging information
  btSerial.begin("ESP32_BlindStick");  // Start Bluetooth with a device name (ESP32 Blind Stick)

  Serial.println("Bluetooth started, waiting for connection...");
}

void loop() {
  // Check if Bluetooth is connected
  if (btSerial.connected()) {
    // Example feedback: Sending "Obstacle detected"
    btSerial.println("Obstacle detected 50 cm ahead");
    delay(1000);  // Adjust delay for more or fewer feedback messages
  } else {
    Serial.println("Waiting for Bluetooth connection...");
  }

  delay(5000);  // Wait for a bit before checking again
}
