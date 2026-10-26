#ifndef LOGBOOT_H
#define LOGBOOT_H
#include <Arduino.h>
#include "display.h"

// Pantalla de arranque sencilla para confirmar que el OLED funciona.
inline void showLogo() {
    Adafruit_SSD1306& display = oledDisplay();
    display.clearDisplay();
    display.drawRoundRect(0, 0, OLED_WIDTH, OLED_HEIGHT, 7, SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(22, 17);
    display.println(F("ROBOT ESP32"));
    display.drawLine(18, 30, 110, 30, SSD1306_WHITE);
    display.setCursor(17, 39);
    display.println(F("OLED + L293D"));
    display.display();
}

inline void testDisplay() {
    Adafruit_SSD1306& display = oledDisplay();
    const int side = 20;
    const int x = (OLED_WIDTH - side) / 2;
    const int y = (OLED_HEIGHT - side) / 2;
    display.clearDisplay();
    display.drawRect(x, y, side, side, SSD1306_WHITE);
    display.display();
    Serial.printf("[OLED POST] Cuadrado centrado en x=%d, y=%d, lado=%d\n", x, y, side);
}
#endif
