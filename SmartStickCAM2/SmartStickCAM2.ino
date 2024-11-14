#include "config.h"
#include "esp_camera.h"
#include "BluetoothSerial.h"
#include <Arduino.h>

BluetoothSerial SerialBT;

// Function declarations
float getDistance(int trigPin, int echoPin);
void handleObject(String object);
void speakMessage(String message);
void setupCamera();
String detectObject();

void setup() {
    Serial.begin(115200);
    
    // Initialize pins
    pinMode(TRIGGER_PIN_FRONT, OUTPUT);
    pinMode(ECHO_PIN_FRONT, INPUT);
    pinMode(TRIGGER_PIN_RIGHT, OUTPUT);
    pinMode(ECHO_PIN_RIGHT, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(IR_SENSOR_PIN, INPUT);
    
    // Initialize Bluetooth
    SerialBT.begin(BT_DEVICE_NAME);
    
    // Initialize camera
    setupCamera();
    
    speakMessage("Smart stick initialized");
}

void loop() {
    // Get distances from sensors
    float frontDistance = getDistance(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
    float rightDistance = getDistance(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
    
    // Check for obstacles
    if (frontDistance < CRITICAL_DISTANCE) {
        speakMessage("Warning: Very close obstacle ahead");
        digitalWrite(BUZZER_PIN, HIGH);
        delay(200);
        digitalWrite(BUZZER_PIN, LOW);
    }
    else if (frontDistance < DISTANCE_THRESHOLD) {
        speakMessage("Obstacle ahead");
    }
    
    if (rightDistance < DISTANCE_THRESHOLD) {
        speakMessage("Obstacle on right");
    }
    
    // Check for potholes
    int irValue = analogRead(IR_SENSOR_PIN);
    if (irValue < 500) {
        speakMessage("Warning: Pothole detected");
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
    }
    
    // Object detection
    String detectedObject = detectObject();
    if (detectedObject != "") {
        handleObject(detectedObject);
    }
    
    delay(SAMPLE_TIME);
}

float getDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    return duration * 0.034 / 2;
}

void handleObject(String object) {
    float distance = getDistance(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
    String message = object + " detected";
    if (distance < DISTANCE_THRESHOLD) {
        message += " nearby";
    }
    speakMessage(message);
}

void setupCamera() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        speakMessage("Camera initialization failed");
        return;
    }
}

void speakMessage(String message) {
    if (SerialBT.connected()) {
        SerialBT.println(message);
    }
    Serial.println(message); // For debugging
}

String detectObject() {
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        return "";
    }
    
    // Simulated object detection
    // Replace with actual AI model implementation
    static unsigned long lastDetection = 0;
    static const String objects[] = {"person", "vehicle", "stairs", "door"};
    
    if (millis() - lastDetection > 5000) {
        lastDetection = millis();
        esp_camera_fb_return(fb);
        return objects[random(0, 4)];
    }
    
    esp_camera_fb_return(fb);
    return "";
}