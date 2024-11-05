#ifndef AUDIO_FEEDBACK_H
#define AUDIO_FEEDBACK_H

#include "BluetoothSerial.h"

class AudioFeedback {
private:
    uint8_t buzzerPin;
    BluetoothSerial SerialBT;
    
public:
    AudioFeedback(uint8_t pin);
    void init();
    void playAlert(int duration);
    void speak(String message);
};

#endif