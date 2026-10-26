#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

inline Adafruit_SSD1306& oledDisplay() {
    static Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET_PIN);
    return display;
}

inline void initDisplay() {
    if (!oledDisplay().begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
        Serial.println(F("[ERROR] No se pudo inicializar el OLED SSD1306."));
        while (true) { delay(100); }
    }
    oledDisplay().clearDisplay();
    oledDisplay().setTextColor(SSD1306_WHITE);
    oledDisplay().display();
    Serial.println(F("[OLED] Panel listo: 128x64."));
}
#endif
