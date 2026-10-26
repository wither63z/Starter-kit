#ifndef MOTOR_LEDS_H
#define MOTOR_LEDS_H
#include <Arduino.h>
#include "config.h"

inline const int* motorLedPins() {
    static const int pins[] = {MOTOR_A1_PIN, MOTOR_A2_PIN, MOTOR_B1_PIN, MOTOR_B2_PIN};
    return pins;
}

inline void allMotorLedsOff() {
    const int* pins = motorLedPins();
    for (int i = 0; i < 4; i++) {
        digitalWrite(pins[i], LOW);
    }
}

inline void initMotorLeds() {
    const int* pins = motorLedPins();
    for (int i = 0; i < 4; i++) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], LOW);
    }
    Serial.println(F("[L293D] Salidas preparadas: GPIO 25, 26, 32 y 27."));
}

inline void updateMotorLeds() {
    static const char* labels[] = {"Motor A - entrada 1", "Motor A - entrada 2",
                                   "Motor B - entrada 1", "Motor B - entrada 2"};
    static int index = 0;
    static unsigned long lastChange = 0;
    static unsigned long pauseStart = 0;
    static bool waitingPause = false;
    static bool started = false;

    const unsigned long now = millis();
    const int* pins = motorLedPins();

    if (!started) {
        allMotorLedsOff();
        digitalWrite(pins[0], HIGH);
        Serial.println(F("[L293D] LED de prueba encendido: Motor A - entrada 1"));
        lastChange = now;
        started = true;
        return;
    }

    if (waitingPause) {
        if (now - pauseStart >= MOTOR_LED_PAUSE_MS) {
            waitingPause = false;
            index = 0;
            digitalWrite(pins[index], HIGH);
            Serial.println(F("[L293D] LED de prueba encendido: Motor A - entrada 1"));
            lastChange = now;
        }
        return;
    }

    if (now - lastChange < MOTOR_LED_INTERVAL_MS) {
        return;
    }

    allMotorLedsOff();
    index++;
    if (index >= 4) {
        waitingPause = true;
        pauseStart = now;
        Serial.println(F("[L293D] Secuencia terminada; pausa."));
        return;
    }

    digitalWrite(pins[index], HIGH);
    Serial.print(F("[L293D] LED de prueba encendido: "));
    Serial.println(labels[index]);
    lastChange = now;
}
#endif
