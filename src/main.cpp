#include <Arduino.h>
#include <OneButton.h>

// Phần cứng
#define LED1_PIN LED_BUILTIN
#define LED2_PIN 5
#define BUTTON_PIN 4

OneButton button(BUTTON_PIN, true); // true: pull-up

bool ledState1 = false;
bool ledState2 = false;
bool controlLED1 = true; // true -> đang điều khiển LED1
bool blinking = false;

unsigned long lastBlink = 0;
const int blinkInterval = 200; // ms

void singleClick() {
    if(controlLED1){
        ledState1 = !ledState1;
        digitalWrite(LED1_PIN, ledState1);
    } else {
        ledState2 = !ledState2;
        digitalWrite(LED2_PIN, ledState2);
    }
}

void doubleClick() {
    controlLED1 = !controlLED1; // đổi LED điều khiển
}

void longPressStart() {
    blinking = true;
}

void longPressStop() {
    blinking = false;
    // Tắt LED đang nhấp nháy
    if(controlLED1) digitalWrite(LED1_PIN, ledState1);
    else digitalWrite(LED2_PIN, ledState2);
}

void setup() {
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);

    button.attachClick(singleClick);
    button.attachDoubleClick(doubleClick);
    button.attachLongPressStart(longPressStart);
    button.attachLongPressStop(longPressStop);
}

void loop() {
    button.tick();

    if(blinking){
        unsigned long now = millis();
        if(now - lastBlink >= blinkInterval){
            lastBlink = now;
            if(controlLED1){
                digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));
            } else {
                digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));
            }
        }
    }
}
