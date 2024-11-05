#include "AudioFeedback.h"
#include "config.h"

AudioFeedback::AudioFeedback(uint8_t pin) {
    buzzerPin = pin;
}

void AudioFeedback::init() {
    pinMode(buzzerPin, OUTPUT);
    SerialBT.begin(BT_DEVICE_NAME);
}

void AudioFeedback::playAlert(int duration) {
    digitalWrite(buzzerPin, HIGH);
    delay(duration);
    digitalWrite(buzzerPin, LOW);
}

void AudioFeedback::speak(String message) {
    if (SerialBT.connected()) {
        SerialBT.println(message);
    }
}