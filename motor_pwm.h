#ifndef MOTOR_PWM_H
#define MOTOR_PWM_H
#include <Arduino.h>
#include <esp_arduino_version.h>
#include "config.h"

inline void writeMotorPwm(uint8_t speed);

inline bool initMotorPwm() {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
    const bool motorAReady = ledcAttachChannel(
        MOTOR_A_ENABLE_PIN, MOTOR_PWM_FREQUENCY_HZ,
        MOTOR_PWM_RESOLUTION_BITS, MOTOR_PWM_CHANNEL_A);
    const bool motorBReady = ledcAttachChannel(
        MOTOR_B_ENABLE_PIN, MOTOR_PWM_FREQUENCY_HZ,
        MOTOR_PWM_RESOLUTION_BITS, MOTOR_PWM_CHANNEL_B);
    if (!motorAReady || !motorBReady) {
        Serial.println(F("[ERROR] No se pudieron configurar los canales PWM LEDC."));
        return false;
    }
#else
    ledcSetup(MOTOR_PWM_CHANNEL_A, MOTOR_PWM_FREQUENCY_HZ, MOTOR_PWM_RESOLUTION_BITS);
    ledcSetup(MOTOR_PWM_CHANNEL_B, MOTOR_PWM_FREQUENCY_HZ, MOTOR_PWM_RESOLUTION_BITS);
    ledcAttachPin(MOTOR_A_ENABLE_PIN, MOTOR_PWM_CHANNEL_A);
    ledcAttachPin(MOTOR_B_ENABLE_PIN, MOTOR_PWM_CHANNEL_B);
#endif
    writeMotorPwm(0);
    Serial.printf("[PWM] Canales %d/%d, %lu Hz, resolucion %d bits. ENA=GPIO %d, ENB=GPIO %d.\n",
                  MOTOR_PWM_CHANNEL_A, MOTOR_PWM_CHANNEL_B,
                  (unsigned long)MOTOR_PWM_FREQUENCY_HZ, MOTOR_PWM_RESOLUTION_BITS,
                  MOTOR_A_ENABLE_PIN, MOTOR_B_ENABLE_PIN);
    return true;
}

inline void writeMotorPwm(uint8_t speed) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
    const bool motorAUpdated = ledcWriteChannel(MOTOR_PWM_CHANNEL_A, speed);
    const bool motorBUpdated = ledcWriteChannel(MOTOR_PWM_CHANNEL_B, speed);
    if (!motorAUpdated || !motorBUpdated) {
        Serial.println(F("[ERROR] No se pudo actualizar la salida PWM de los motores."));
    }
#else
    ledcWrite(MOTOR_PWM_CHANNEL_A, speed);
    ledcWrite(MOTOR_PWM_CHANNEL_B, speed);
#endif
}
#endif
