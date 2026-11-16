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

// L293D: entradas de direccion y habilitaciones PWM de los motores.
#define MOTOR_A1_PIN 25
#define MOTOR_A2_PIN 26
#define MOTOR_B1_PIN 32
#define MOTOR_B2_PIN 27
#define MOTOR_A_ENABLE_PIN 33
#define MOTOR_B_ENABLE_PIN 14
#define MOTOR_PWM_FREQUENCY_HZ 20000
#define MOTOR_PWM_RESOLUTION_BITS 8
#define MOTOR_PWM_CHANNEL_A 0
#define MOTOR_PWM_CHANNEL_B 1
#define MOTOR_DEFAULT_SPEED 180
#define MOTOR_SPEED_STEP 25

#define EYES_MAX_FPS 60
#define LOGO_TIME_MS 3000
