// main.cpp
// Integra los ojos OLED con el control de motores por L293D.
// Pines reservados para OLED: GPIO 21 (SDA) y GPIO 22 (SCL).

#include <Arduino.h>

#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logboot.h"
#include "eyes.h"
#include "debug_serial.h"
#include "motor_control.h"

bool bootComplete = false;
unsigned long bootTime = 0;

void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println(F("\n[BOOT] Sistema de ojos OLED + motores L293D"));

    // 1. Iniciar y comprobar el bus I2C.
    initI2C();
    scanI2C();
    testI2CDevice();

    // 2. Preparar la pantalla y mostrar el logo de arranque.
    initDisplay();
    showLogo();
    testDisplay();
    showLogo();

    // 3. Iniciar RoboEyes y preparar direccion y PWM de los motores.
    initEyes();
    if (!initMotors()) {
        while (true) {
            delay(100);
        }
    }

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

    // Los ojos se actualizan cuando los motores estan detenidos.
    debugSerialTick();
    if (!motorIsMoving()) {
        updateEyes();
    }
}
