#include <Arduino.h>

// GPIO de control de los cuatro relés
const int relayA = 16;
const int relayB = 17;
const int relayC = 18;
const int relayD = 19;

// El módulo de relés se considera activo en LOW
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;

const unsigned long interval = 2000;

const int relays[] = {relayA, relayB, relayC, relayD};
const char* names[] = {"A", "B", "C", "D"};

void allOff() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(relays[i], RELAY_OFF);
  }
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 4; i++) {
    // Fija primero el nivel inactivo para evitar pulsos al arrancar.
    digitalWrite(relays[i], RELAY_OFF);
    pinMode(relays[i], OUTPUT);
  }

  allOff();
  Serial.println("Secuencia automatica iniciada");
}

void loop() {
  for (int i = 0; i < 4; i++) {
    allOff();
    digitalWrite(relays[i], RELAY_ON);

    Serial.print("LED encendido: ");
    Serial.println(names[i]);

    delay(interval);
  }

  allOff();
  delay(1000);
}
