#ifndef EYES_H
#define EYES_H
#include <Arduino.h>
#include "display.h"
#include "config.h"

#undef DEFAULT
#include <FluxGarage_RoboEyes.h>

// La pantalla se obtiene de display.h para compartir una sola instancia.
inline RoboEyes<Adafruit_SSD1306>& roboEyesInstance() {
    static RoboEyes<Adafruit_SSD1306> eyes(oledDisplay());
    return eyes;
}

inline void initEyes() {
    roboEyesInstance().begin(OLED_WIDTH, OLED_HEIGHT, EYES_MAX_FPS);
    roboEyesInstance().setMood(DEFAULT);
    roboEyesInstance().setPosition(DEFAULT);
    roboEyesInstance().setAutoblinker(true, 3, 2);
    roboEyesInstance().setIdleMode(true, 2, 1);
    Serial.printf("[EYES] Ojos listos a %d FPS. Teclas 1-7 para expresiones.\n", EYES_MAX_FPS);
}

inline void updateEyes() {
    roboEyesInstance().update();
}

inline void setEyesMood(char key) {
    // Limpiar la expresion anterior antes de aplicar la nueva.
    roboEyesInstance().setMood(DEFAULT);
    roboEyesInstance().setPosition(DEFAULT);
    roboEyesInstance().setCuriosity(false);
    roboEyesInstance().setSweat(false);

    switch (key) {
        case '1':
            roboEyesInstance().setMood(DEFAULT);
            Serial.println(F("[EYES] Expresion 1: normal"));
            break;
        case '2':
            roboEyesInstance().setMood(HAPPY);
            Serial.println(F("[EYES] Expresion 2: feliz"));
            break;
        case '3':
            roboEyesInstance().setMood(TIRED);
            Serial.println(F("[EYES] Expresion 3: cansado"));
            break;
        case '4':
            roboEyesInstance().setMood(ANGRY);
            Serial.println(F("[EYES] Expresion 4: enfadado"));
            break;
        case '5':
            roboEyesInstance().setPosition(N);
            roboEyesInstance().setCuriosity(true);
            Serial.println(F("[EYES] Expresion 5: mirando arriba"));
            break;
        case '6':
            roboEyesInstance().setMood(HAPPY);
            roboEyesInstance().anim_laugh();
            Serial.println(F("[EYES] Expresion 6: risa"));
            break;
        case '7':
            roboEyesInstance().anim_confused();
            Serial.println(F("[EYES] Expresion 7: confundido"));
            break;
        default:
            break;
    }
}
#endif
