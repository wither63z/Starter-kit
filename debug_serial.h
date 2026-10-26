#ifndef DEBUG_SERIAL_H
#define DEBUG_SERIAL_H
#include <Arduino.h>
#include "eyes.h"

inline void printHelp() {
    Serial.println();
    Serial.println(F("=== CONTROL DE OJOS OLED ==="));
    Serial.println(F("1 - Normal"));
    Serial.println(F("2 - Feliz"));
    Serial.println(F("3 - Cansado"));
    Serial.println(F("4 - Enfadado"));
    Serial.println(F("5 - Mirar arriba"));
    Serial.println(F("6 - Reir"));
    Serial.println(F("7 - Confundido"));
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
        } else if (key == '\r' || key == '\n' || key == ' ' || key == '\t') {
            // Ignorar silenciosamente caracteres de control y espacios.
        } else {
            Serial.printf("[SERIAL] Tecla no reconocida: %c\n", key);
        }
    }
}
#endif
