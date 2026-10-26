#ifndef I2C_MANAGER_H
#define I2C_MANAGER_H
#include <Arduino.h>
#include <Wire.h>
#include "config.h"

inline void initI2C() {
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_FREQUENCY_HZ);
    Serial.printf("[I2C] Bus listo SDA=%d SCL=%d a %lu Hz\n",
                  I2C_SDA_PIN, I2C_SCL_PIN,
                  (unsigned long)I2C_FREQUENCY_HZ);
}

inline void scanI2C() {
    uint8_t found = 0;
    Serial.println(F("[I2C] Buscando dispositivos..."));
    for (uint8_t address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            Serial.printf("[I2C] Dispositivo encontrado en 0x%02X\n", address);
            found++;
        }
    }
    Serial.printf("[I2C] Barrido terminado. Dispositivos: %u\n", found);
}

inline bool testI2CDevice() {
    Wire.beginTransmission(OLED_I2C_ADDRESS);
    const uint8_t error = Wire.endTransmission();
    if (error == 0) {
        Serial.printf("[I2C] OLED responde en 0x%02X\n", OLED_I2C_ADDRESS);
        return true;
    }
    Serial.printf("[ERROR] No responde el OLED en 0x%02X. Revisa SDA, SCL, VCC y GND. Codigo: %u\n",
                  OLED_I2C_ADDRESS, error);
    while (true) {
        delay(100);
    }
}
#endif
