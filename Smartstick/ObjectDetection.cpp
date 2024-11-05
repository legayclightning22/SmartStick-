#include "ObjectDetection.h"
#include "config.h"
#include <TensorFlowLite_ESP32.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

ObjectDetection::ObjectDetection() {
    modelLoaded = false;
}

bool ObjectDetection::init() {
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
    config.pixel_format = PIXFORMAT_RGB565;
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        return false;
    }

    static tflite::MicroErrorReporter micro_error_reporter;
    error_reporter = &micro_error_reporter;
    
    model = tflite::GetModel(g_model);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        return false;
    }

    static tflite::AllOpsResolver resolver;
    static tflite::MicroInterpreter static_interpreter(
        model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
    interpreter = &static_interpreter;

    TfLiteStatus allocate_status = interpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk) {
        return false;
    }

    modelLoaded = true;
    return true;
}

String ObjectDetection::detectObject() {
    if (!modelLoaded) {
        return "Model not loaded";
    }
    
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
        return "Camera capture failed";
    }

    // Convert frame buffer to input tensor format
    uint8_t* input = interpreter->input(0)->data.uint8;
    for (int i = 0; i < fb->len; i++) {
        input[i] = fb->buf[i];
    }

    // Run inference
    if (interpreter->Invoke() != kTfLiteOk) {
        esp_camera_fb_return(fb);
        return "Inference failed";
    }

    // Get output and find highest confidence prediction
    TfLiteTensor* output = interpreter->output(0);
    float maxConfidence = 0;
    int maxIndex = 0;
    
    for (int i = 0; i < 3; i++) {  // Assuming 3 classes: person, vehicle, obstacle
        if (output->data.f[i] > maxConfidence) {
            maxConfidence = output->data.f[i];
            maxIndex = i;
        }
    }

    esp_camera_fb_return(fb);

    // Return detected object with confidence
    if (maxConfidence > 0.6) {  // Confidence threshold
        switch (maxIndex) {
            case 0: return "person";
            case 1: return "vehicle";
            case 2: return "obstacle";
            default: return "unknown";
        }
    }
    
    return "";
}