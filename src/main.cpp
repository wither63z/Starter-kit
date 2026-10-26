// main.cpp
// Integra los ojos animados RoboEyes con la secuencia de prueba del L293D.
// Pines reservados para OLED: GPIO 21 (SDA) y GPIO 22 (SCL).

#include <Arduino.h>

// Integra los ojos animados RoboEyes con la secuencia de prueba del L293D.
// Pines reservados para OLED: GPIO 21 (SDA) y GPIO 22 (SCL).

#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logboot.h"
#include "eyes.h"
#include "debug_serial.h"
#include "motor_leds.h"

bool bootComplete = false;
unsigned long bootTime = 0;

unsigned long lastLedChange = 0;
unsigned long ledPauseStart = 0;
int ledIndex = 0;
bool ledPause = false;

void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println(F("\n[BOOT] Sistema de ojos OLED + prueba L293D"));

    // 1. Iniciar y comprobar el bus I2C.
    initI2C();
    scanI2C();
    testI2CDevice();

    // 2. Preparar la pantalla y mostrar el logo de arranque.
    initDisplay();
    showLogo();
    testDisplay();
    showLogo();

    // 3. Iniciar RoboEyes y preparar las salidas del L293D.
    initEyes();
    initMotorLeds();

    printHelp();
    bootTime = millis();
    Serial.println(F("[BOOT] Logo visible durante 3 segundos."));
}

void loop() {
    // Mantener el logo durante la ventana inicial sin bloquear el programa.
    if (!bootComplete) {
        if (millis() - bootTime >= LOGO_TIME_MS) {
            bootComplete = true;
            Serial.println(F("[BOOT] Arranque terminado. Animaciones activas."));
        } else {
            return;
        }
    }

    // Estas funciones no usan delay(): los ojos siguen animándose mientras
    // se atienden los comandos y se cambia la salida del L293D.
    debugSerialTick();
    updateEyes();
    updateMotorLeds();
}
