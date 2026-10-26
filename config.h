#pragma once
#include <Arduino.h>

// OLED SSD1306: estos pines se reservan exclusivamente para I2C.
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22
#define I2C_FREQUENCY_HZ 400000
#define OLED_I2C_ADDRESS 0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET_PIN -1

// L293D: cuatro entradas de control conectadas al ESP32.
// Los LEDs representan las salidas de los dos motores.
#define MOTOR_A1_PIN 25
#define MOTOR_A2_PIN 26
#define MOTOR_B1_PIN 32
#define MOTOR_B2_PIN 27
#define MOTOR_LED_INTERVAL_MS 2000
#define MOTOR_LED_PAUSE_MS 1000

#define EYES_MAX_FPS 60
#define LOGO_TIME_MS 3000
