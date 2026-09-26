#include "state.h"
#include "position.h"
#include "config.h"

void update_state(uint8_t move_towards_open, uint8_t move_towards_locked){
    if (move_towards_open && move_towards_locked){
        return; // both pressed - ignore
    }

    switch (get_position()){ // always read the real position from the sensors
        case ST_OPEN:
            if (move_towards_locked){
                open_to_semi();
            }
        break;

        case ST_SEMI:
            if (move_towards_locked){
                semi_to_locked();
            }
            if (move_towards_open){
                semi_to_open();
            }
        break;

        case ST_LOCKED:
            if (move_towards_open){
                locked_to_semi();
            }
        break;

        case ST_UNKNOWN:
            DEBUG_PRINT("diff: position unknown - not moving");
        break;
    }
}

// Runs in the CAN interrupt. buf[0] = left paddle (towards open), buf[1] = right paddle (towards locked)
void can_callback(const CAN_message_t &msg){
    if (msg.len < 2) return;
    update_state(msg.buf[0], msg.buf[1]);
}
