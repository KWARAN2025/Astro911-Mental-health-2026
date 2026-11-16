// Astro911 - button controller
// Wire each button between its pin and GND (no resistor needed, we use INPUT_PULLUP).
//   D2 = minus / move up
//   D3 = plus / move down
//   D4 = select
//   D5 = back

#include <Arduino_RouterBridge.h>

const int COUNT = 4;
const int PINS[COUNT] = {2, 3, 4, 5};
const char* NAMES[COUNT] = {"minus", "plus", "select", "back"};

int lastState[COUNT];
unsigned long lastChange[COUNT];
const unsigned long DEBOUNCE_MS = 40;

void setup() {
  Bridge.begin();
  for (int i = 0; i < COUNT; i++) {
    pinMode(PINS[i], INPUT_PULLUP);
    lastState[i] = HIGH;
    lastChange[i] = 0;
  }
}

void loop() {
  unsigned long now = millis();
  for (int i = 0; i < COUNT; i++) {
    int state = digitalRead(PINS[i]);
    if (state != lastState[i] && now - lastChange[i] > DEBOUNCE_MS) {
      lastChange[i] = now;
      lastState[i] = state;
      if (state == LOW) {  // pressed (pin pulled to GND)
        Bridge.notify("button_pressed", String(NAMES[i]));
      }
    }
  }
}