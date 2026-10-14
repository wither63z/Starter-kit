/*
  ESP32 LED Blink Test
  Hecho para probar si la carga del código funciona correctamente.
*/
#include <Arduino.h>

// La mayoría de las placas ESP32 tienen el LED interno en el GPIO 2
const int LED_PIN = 2; 

void setup() {
  // Inicializa el puerto serie para ver mensajes en el monitor
  Serial.begin(115200);
  Serial.println("--- ESP32 Listo para la prueba de parpadeo ---");
  
  // Configura el pin del LED como salida
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Enciende el LED
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED Encendido (HIGH)");
  delay(500); // Espera medio segundo

  // Apaga el LED
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED Apagado (LOW)");
  delay(500); // Espera medio segundo
}
