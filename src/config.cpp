#include "config.h"
#include "position.h"
#include "core_pins.h"

#define DIFF_ADDRESS 50
bool debug_flag = false;
FLEX_CAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can;

void initalize(){
    if (debug_flag){
        Serial.begin(115200);
    }

    can.begin();
    can.setBaudRate(500000);
    can.setMBFilter(REJECT_ALL);
    can.setMBFilter(MB0, 0x51);
    can.onReceive(MB0, can_callback);
    can.enableMBInterrupts();
    
    pinMode(MOTOR_POSITION1_PIN, INPUT);
    pinMode(MOTOR_POSITION2_PIN, INPUT);
    pinMode(MOTOR_POSITION3_PIN,INPUT);

    pinMode(OPEN_CONTROL_PIN1, OUTPUT);
    pinMode(OPEN_CONTROL_PIN2, OUTPUT);
    pinMode(LOCK_CONTROL_PIN1, OUTPUT);
    pinMode(LOCK_CONTROL_PIN2, OUTPUT);

    stop_motor();
}
