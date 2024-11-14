```markdown
# Smart Blind Stick - ESP32-CAM Version

## Overview
This project implements a smart blind stick using an ESP32-CAM module. It features:
- Ultrasonic sensors for obstacle detection
- IR sensor for pothole detection
- Camera for object detection
- Bluetooth audio feedback
- Built-in LED for visual alerts

## Hardware Requirements
1. ESP32-CAM module
2. 2x HC-SR04 Ultrasonic Sensors
3. IR Sensor
4. Bluetooth speaker/headphones
5. 18650 Battery
6. Voltage Regulator (5V)

## Pin Connections
1. Front Ultrasonic Sensor
   - VCC -> 5V
   - GND -> GND
   - TRIG -> GPIO13
   - ECHO -> GPIO12

2. Right Ultrasonic Sensor
   - VCC -> 5V
   - GND -> GND
   - TRIG -> GPIO14
   - ECHO -> GPIO15

3. IR Sensor
   - VCC -> 3.3V
   - GND -> GND
   - OUT -> GPIO16

4. Built-in LED (used as buzzer)
   - GPIO2 (built-in)

## Setup Instructions
1. Install required libraries:
   - ESP32 Board Support
   - BluetoothSerial
   - ESP32 Camera Driver

2. Upload the code:
   - Connect ESP32-CAM via FTDI programmer
   - Select "AI Thinker ESP32-CAM" board
   - Upload sketch

3. Testing:
   - Power up the device
   - Connect to "SmartStick" via Bluetooth
   - Test obstacle detection
   - Verify audio feedback

## Safety Notes
- Test thoroughly before actual use
- Keep battery charged
- Regular maintenance checks
- Clean sensors regularly
```