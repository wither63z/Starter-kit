#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "motor_pwm.h"

enum class MotorMotion : uint8_t {
    Stopped,
    Forward,
    Backward,
    Left,
    Right
};

inline MotorMotion& motorMotionState() {
    static MotorMotion motion = MotorMotion::Stopped;
    return motion;
}

inline uint8_t& motorSpeedState() {
    static uint8_t speed = MOTOR_DEFAULT_SPEED;
    return speed;
}

inline bool motorIsMoving() {
    return motorMotionState() != MotorMotion::Stopped;
}

inline const __FlashStringHelper* motorMotionName() {
    switch (motorMotionState()) {
        case MotorMotion::Forward: return F("AVANZAR");
        case MotorMotion::Backward: return F("RETROCEDER");
        case MotorMotion::Left: return F("GIRAR IZQUIERDA");
        case MotorMotion::Right: return F("GIRAR DERECHA");
        default: return F("DETENIDO");
    }
}

inline void showMotorStatus() {
    Adafruit_SSD1306& display = oledDisplay();
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(F("CONTROL DE MOTORES"));
    display.drawLine(0, 11, OLED_WIDTH - 1, 11, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 20);
    display.println(motorMotionName());
    display.setCursor(0, 36);
    display.print(F("Velocidad: "));
    display.print(motorSpeedState());
    display.println(F("/255"));
    display.drawRect(0, 52, OLED_WIDTH, 10, SSD1306_WHITE);
    const int barWidth = (int)motorSpeedState() * (OLED_WIDTH - 2) / 255;
    if (barWidth > 0) {
        display.fillRect(1, 53, barWidth, 8, SSD1306_WHITE);
    }
    display.display();
}

inline void setMotorDirection(bool motorAForward, bool motorBForward) {
    digitalWrite(MOTOR_A1_PIN, motorAForward ? HIGH : LOW);
    digitalWrite(MOTOR_A2_PIN, motorAForward ? LOW : HIGH);
    digitalWrite(MOTOR_B1_PIN, motorBForward ? HIGH : LOW);
    digitalWrite(MOTOR_B2_PIN, motorBForward ? LOW : HIGH);
}

inline void applyMotorMotion(MotorMotion motion, bool motorAForward, bool motorBForward) {
    writeMotorPwm(0);
    if (motion == MotorMotion::Stopped || motorSpeedState() == 0) {
        digitalWrite(MOTOR_A1_PIN, LOW);
        digitalWrite(MOTOR_A2_PIN, LOW);
        digitalWrite(MOTOR_B1_PIN, LOW);
        digitalWrite(MOTOR_B2_PIN, LOW);
        motorMotionState() = MotorMotion::Stopped;
    } else {
        setMotorDirection(motorAForward, motorBForward);
        writeMotorPwm(motorSpeedState());
        motorMotionState() = motion;
    }
    if (motorIsMoving()) {
        showMotorStatus();
    }
    Serial.print(F("[MOTORES] "));
    Serial.print(motorMotionName());
    Serial.printf(" | velocidad %u/255\n", motorSpeedState());
}

inline void moveForward() {
    applyMotorMotion(MotorMotion::Forward, true, true);
}

inline void moveBackward() {
    applyMotorMotion(MotorMotion::Backward, false, false);
}

inline void turnLeft() {
    applyMotorMotion(MotorMotion::Left, false, true);
}

inline void turnRight() {
    applyMotorMotion(MotorMotion::Right, true, false);
}

inline void stopMotors() {
    applyMotorMotion(MotorMotion::Stopped, false, false);
}

inline void setMotorSpeed(uint8_t speed) {
    motorSpeedState() = speed;
    if (speed == 0 && motorIsMoving()) {
        stopMotors();
    } else if (motorIsMoving()) {
        writeMotorPwm(speed);
        showMotorStatus();
    }
    Serial.printf("[MOTORES] Velocidad ajustada: %u/255\n", speed);
}

inline void changeMotorSpeed(int delta) {
    int speed = (int)motorSpeedState() + delta;
    if (speed < 0) speed = 0;
    if (speed > 255) speed = 255;
    setMotorSpeed((uint8_t)speed);
}

inline bool initMotors() {
    pinMode(MOTOR_A1_PIN, OUTPUT);
    pinMode(MOTOR_A2_PIN, OUTPUT);
    pinMode(MOTOR_B1_PIN, OUTPUT);
    pinMode(MOTOR_B2_PIN, OUTPUT);
    digitalWrite(MOTOR_A1_PIN, LOW);
    digitalWrite(MOTOR_A2_PIN, LOW);
    digitalWrite(MOTOR_B1_PIN, LOW);
    digitalWrite(MOTOR_B2_PIN, LOW);
    if (!initMotorPwm()) {
        return false;
    }
    Serial.println(F("[MOTORES] Entradas de direccion listas."));
    return true;
}
#endif
