#ifndef DEBUG_SERIAL_H
#define DEBUG_SERIAL_H
#include <Arduino.h>
#include "eyes.h"
#include "motor_control.h"

inline void printHelp() {
    Serial.println();
    Serial.println(F("=== CONTROL DE MOTORES Y OJOS OLED ==="));
    Serial.println(F("1 - Normal"));
    Serial.println(F("2 - Feliz"));
    Serial.println(F("3 - Cansado"));
    Serial.println(F("4 - Enfadado"));
    Serial.println(F("5 - Mirar arriba"));
    Serial.println(F("6 - Reir"));
    Serial.println(F("7 - Confundido"));
    Serial.println(F("w - Avanzar | s - Retroceder"));
    Serial.println(F("a - Girar izquierda | d - Girar derecha | x - Detener"));
    Serial.println(F("+ / - - Subir / bajar velocidad"));
    Serial.println(F("h - Mostrar esta ayuda"));
    Serial.println(F("Monitor Serie: 115200 baudios"));
    Serial.println(F("============================"));
}

inline void debugSerialTick() {
    while (Serial.available() > 0) {
        const char key = (char)Serial.read();
        if (key == 'h' || key == 'H') {
            printHelp();
        } else if (key >= '1' && key <= '7') {
            setEyesMood(key);
        } else if (key == 'w' || key == 'W') {
            moveForward();
        } else if (key == 's' || key == 'S') {
            moveBackward();
        } else if (key == 'a' || key == 'A') {
            turnLeft();
        } else if (key == 'd' || key == 'D') {
            turnRight();
        } else if (key == 'x' || key == 'X') {
            stopMotors();
        } else if (key == '+') {
            changeMotorSpeed(MOTOR_SPEED_STEP);
        } else if (key == '-') {
            changeMotorSpeed(-MOTOR_SPEED_STEP);
        } else if (key == '\r' || key == '\n' || key == ' ' || key == '\t') {
            // Ignorar silenciosamente caracteres de control y espacios.
        } else {
            Serial.printf("[SERIAL] Tecla no reconocida: %c\n", key);
        }
    }
}
#endif
