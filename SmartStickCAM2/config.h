#ifndef CONFIG_H
#define CONFIG_H

// Pin Configurations for ESP32-CAM
#define TRIGGER_PIN_FRONT 13
#define ECHO_PIN_FRONT    12
#define TRIGGER_PIN_RIGHT 14
#define ECHO_PIN_RIGHT    15
#define BUZZER_PIN        2   // Flash LED pin used as buzzer
#define IR_SENSOR_PIN     16

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
#define DISTANCE_THRESHOLD 150  // cm
#define CRITICAL_DISTANCE  50   // cm
#define SAMPLE_TIME       100   // ms
#define BT_DEVICE_NAME    "SmartStick"

#endif