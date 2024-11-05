#ifndef CONFIG_H
#define CONFIG_H

// Pin Configurations
#define TRIGGER_PIN_FRONT 12
#define ECHO_PIN_FRONT    13
#define TRIGGER_PIN_RIGHT 14
#define ECHO_PIN_RIGHT    15
#define TRIGGER_PIN_LEFT  16
#define ECHO_PIN_LEFT     17
#define BUZZER_PIN        18

// Camera pins (ESP32-CAM)
#define CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// Constants
#define DISTANCE_THRESHOLD 100  // cm
#define CRITICAL_DISTANCE 50    // cm for immediate alerts
#define SAMPLE_TIME       100   // ms
#define BT_DEVICE_NAME    "SmartStick"
#define BATTERY_PIN       34    // Battery voltage monitoring
#define LOW_BATTERY_THRESHOLD 3.3 // Volts

// Error codes
#define ERR_SENSOR_INIT   1
#define ERR_CAMERA_INIT   2
#define ERR_BT_INIT       3
#define ERR_LOW_BATTERY   4

#endif