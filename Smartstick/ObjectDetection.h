#ifndef OBJECT_DETECTION_H
#define OBJECT_DETECTION_H

#include "esp_camera.h"
#include <TensorFlowLite_ESP32.h>

class ObjectDetection {
private:
    camera_config_t config;
    bool modelLoaded;
    
public:
    ObjectDetection();
    bool init();
    String detectObject();
    void processFrame();
};

#endif