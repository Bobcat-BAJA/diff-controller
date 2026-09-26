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
        break;

        case ST_UNKNOWN:
            DEBUG_PRINT("diff: position unknown - not moving");
        break;
    }
}

/*CENTER
 *BOTTOM
 *RIGHT
 *TOP
 * */

void can_callback(const int &msg){
    //For the front diff uncomment these and comment the others
    if (msg.buf[5] == 0xFF){
        update_state(0, 1);
    }
    if (msg.buf[2] ==  0xFF ){
        update_state(1, 0);
    }

    //For the rear diff uncomment these and comment the others
    if (msg.buf[3] == 0xFF){
        update_state(0, 1);
    }
    if (msg.buf[1] == 0xFF){
        update_state(1, 0);
    }
}

void default_to_open(){
    DiffState current_state = get_position();

    if (current_state == ST_OPEN){
        return;
    }
    
    if (current_state == ST_SEMI){
        semi_to_open();
        return;
    }

    if (current_state == ST_LOCKED){
        locked_to_semi();
        delay(500);
        semi_to_open();
        return;
    }
    state_message.id = CAN_ID;
    state_message.len = 1;
    state_message.buf[0] = 0x31;
}

void default_to_locked(){
    DiffState = get_position();
    
    if (current_state == ST_OPEN){
        open_to_semi();
        delay(500);
        semi_to_locked();
    }
    
    else if (current_state == ST_SEMI){
        semi_to_locked();
    }
    else if(current_state == ST_LOCKED{
        
    }

    CAN_message_t state_message;
    state_message.id = CAN_ID;
    state_message.len = 1;
    state_message.buf[0] = 0x33;

    can.write(state_message);
    return;
}
