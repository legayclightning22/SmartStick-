# ESP32 Smart Stick Upload Instructions

## Prerequisites

1. Install Arduino IDE
   - Download from: https://www.arduino.cc/en/software
   - Install version 2.0 or newer

2. Install ESP32 Board Support
   - Open Arduino IDE
   - Go to File → Preferences
   - Add to Additional Boards Manager URLs:
     `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Go to Tools → Board → Boards Manager
   - Search for "ESP32"
   - Install "ESP32 by Espressif Systems"

3. Install Required Libraries
   - Go to Tools → Manage Libraries
   - Install the following:
     * TensorFlowLite_ESP32
     * BluetoothSerial
     * ESP32CameraWebServer

## Upload Process

1. Hardware Setup
   - Connect ESP32 to your computer via USB
   - For ESP32-CAM module:
     * Connect GPIO0 to GND (programming mode)
     * Use FTDI adapter or USB-TTL converter:
       - FTDI RX → ESP32 TX (GPIO1)
       - FTDI TX → ESP32 RX (GPIO3)
       - FTDI VCC → ESP32 5V
       - FTDI GND → ESP32 GND

2. IDE Configuration
   - Open Arduino IDE
   - Select correct board:
     * Tools → Board → ESP32 Arduino → AI Thinker ESP32-CAM
   - Select correct port:
     * Tools → Port → [Select your USB port]
   - Set upload speed:
     * Tools → Upload Speed → 115200

3. Upload Steps
4. 1. Open SmartStick.ino in Arduino IDE
   2. Press reset button on ESP32
   3. Click Upload button in Arduino IDE
   4. Wait for "Connecting...." message
   5. Press boot button on ESP32
   6. Wait for upload to complete
   7. Disconnect GPIO0 from GND
   8. Press reset button again
   ```

5. Verification
   - Open Serial Monitor (Tools → Serial Monitor)
   - Set baud rate to 115200
   - You should see initialization messages
   - Check for "Smart stick initialized" message

## Troubleshooting

1. Upload Fails
   - Check USB connection
   - Verify correct port selection
   - Try pressing boot button during upload
   - Check if GPIO0 is properly grounded

2. Camera Issues
   - Verify camera module connections
   - Check if camera is properly seated
   - Try re-flashing firmware

3. Bluetooth Problems
   - Verify Bluetooth is enabled on phone
   - Check BT_DEVICE_NAME in config.h
   - Reset ESP32 and try pairing again

4. Sensor Issues
   - Check wiring connections
   - Verify voltage levels
   - Test sensors individually

## Safety Notes

1. Power Supply
   - Use proper voltage regulator
   - Check battery polarity
   - Monitor battery voltage

2. First Run
   - Test without battery first
   - Verify all sensors work
   - Check Bluetooth connection
   - Test emergency alerts

## Post-Upload Steps

1. Testing
   - Test all ultrasonic sensors
   - Verify camera operation
   - Check Bluetooth connectivity
   - Test battery monitoring

2. Calibration
   - Adjust DISTANCE_THRESHOLD if needed
   - Fine-tune CRITICAL_DISTANCE
   - Calibrate battery voltage readings

3. Final Assembly
   - Secure all connections
   - Apply heat shrink tubing
   - Weatherproof as needed
```
