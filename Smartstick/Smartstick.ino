#include "config.h"
#include "UltrasonicSensor.h"
#include "ObjectDetection.h"
#include "AudioFeedback.h"
#include "esp_sleep.h"
#include "driver/adc.h"

UltrasonicSensor frontSensor(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
UltrasonicSensor rightSensor(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
UltrasonicSensor leftSensor(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
ObjectDetection objectDetection;
AudioFeedback audio(BUZZER_PIN);

// System state
bool systemInitialized = false;
unsigned long lastBatteryCheck = 0;
const unsigned long BATTERY_CHECK_INTERVAL = 60000; // Check battery every minute

float getBatteryVoltage() {
    uint32_t reading = analogRead(BATTERY_PIN);
    return (reading * 3.3 / 4095.0) * 2; // Voltage divider
}

void handleError(uint8_t errorCode) {
    switch(errorCode) {
        case ERR_SENSOR_INIT:
            audio.speak("Error: Sensor initialization failed");
            break;
        case ERR_CAMERA_INIT:
            audio.speak("Error: Camera initialization failed");
            break;
        case ERR_BT_INIT:
            // Flash buzzer in specific pattern for BT error
            for(int i = 0; i < 3; i++) {
                audio.playAlert(100);
                delay(100);
            }
            break;
        case ERR_LOW_BATTERY:
            audio.speak("Warning: Low battery");
            break;
    }
}

void setup() {
    Serial.begin(115200);
    
    // Initialize sensors
    if (!frontSensor.init() || !rightSensor.init() || !leftSensor.init()) {
        handleError(ERR_SENSOR_INIT);
        return;
    }
    
    // Initialize camera and AI
    if (!objectDetection.init()) {
        handleError(ERR_CAMERA_INIT);
        return;
    }
    
    // Initialize audio feedback
    audio.init();
    if (!SerialBT.begin(BT_DEVICE_NAME)) {
        handleError(ERR_BT_INIT);
    }
    
    // Power management
    esp_sleep_enable_timer_wakeup(SAMPLE_TIME * 1000);
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_11db);
    
    systemInitialized = true;
    audio.speak("Smart stick initialized");
}

void loop() {
    if (!systemInitialized) {
        delay(1000);
        return;
    }

    // Check battery periodically
    unsigned long currentMillis = millis();
    if (currentMillis - lastBatteryCheck >= BATTERY_CHECK_INTERVAL) {
        lastBatteryCheck = currentMillis;
        float batteryVoltage = getBatteryVoltage();
        if (batteryVoltage < LOW_BATTERY_THRESHOLD) {
            handleError(ERR_LOW_BATTERY);
        }
    }
    
    // Get distances from sensors
    float frontDistance = frontSensor.getDistance();
    float rightDistance = rightSensor.getDistance();
    float leftDistance = leftSensor.getDistance();
    
    // Critical distance warnings
    if (frontDistance < CRITICAL_DISTANCE) {
        audio.playAlert(500); // Longer alert for critical distance
        audio.speak("Warning: Very close obstacle ahead");
    }
    // Regular distance warnings
    else if (frontDistance < DISTANCE_THRESHOLD) {
        audio.playAlert(200);
        audio.speak("Obstacle ahead");
    }
    
    if (rightDistance < DISTANCE_THRESHOLD) {
        audio.playAlert(100);
        audio.speak("Obstacle on right");
    }
    
    if (leftDistance < DISTANCE_THRESHOLD) {
        audio.playAlert(100);
        audio.speak("Obstacle on left");
    }
    
    // Object detection using AI
    String detectedObject = objectDetection.detectObject();
    if (detectedObject != "") {
        String message = "Detected " + detectedObject;
        if (detectedObject == "person") {
            message += " ahead";
        } else if (detectedObject == "vehicle") {
            message += " approaching";
        }
        audio.speak(message);
    }
    
    // Power saving
    esp_light_sleep_start();
    delay(SAMPLE_TIME);
}