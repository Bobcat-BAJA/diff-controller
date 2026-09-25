#include "config.h"
#include "core_pins.h"
#include "position.h"

bool debug_flag = false;

void initalize(){
    if (debug_flag){
        Serial.begin(115200);
    }
    
    pinMode(MOTOR_POSITION1_PIN, INPUT);
    pinMode(MOTOR_POSITION2_PIN, INPUT);
    pinMode(MOTOR_POSITION3_PIN,INPUT);

    pinMode(OPEN_CONTROL_PIN1, OUTPUT);
    pinMode(OPEN_CONTROL_PIN2, OUTPUT);
    pinMode(LOCK_CONTROL_PIN1, OUTPUT);
    pinMode(LOCK_CONTROL_PIN2, OUTPUT);

    stop_motor();

}
