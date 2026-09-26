#include "config.h"
#include "position.h"
#include "state.h"

bool debug_flag = false;
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can;

void initialize(){
    if (debug_flag){
        Serial.begin(115200);
    }

    // Pins first: the CAN interrupt can start a move as soon as it is enabled.
    pinMode(MOTOR_POSITION1_PIN, INPUT);
    pinMode(MOTOR_POSITION2_PIN, INPUT);
    pinMode(MOTOR_POSITION3_PIN, INPUT);

    pinMode(OPEN_CONTROL_PIN1, OUTPUT);
    pinMode(OPEN_CONTROL_PIN2, OUTPUT);
    pinMode(LOCK_CONTROL_PIN1, OUTPUT);
    pinMode(LOCK_CONTROL_PIN2, OUTPUT);
    stop_motor();

    can.begin();
    can.setBaudRate(500000);
    can.setMBFilter(REJECT_ALL);
    can.setMBFilter(MB0, DIFF_CAN_ID);
    can.onReceive(MB0, can_callback);
    can.enableMBInterrupts();
}
