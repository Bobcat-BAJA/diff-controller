#include <Arduino.h>
#include "config.h"

void setup() {
    initialize();
}

void loop() {
    // Nothing: can_callback runs from the CAN RX interrupt
    // (FlexCAN_T4 calls it directly as long as can.events() is never used).
}
