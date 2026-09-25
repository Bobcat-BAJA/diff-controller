#include "state.h"
#include <cstdint>
#include "position.h"

FLEXCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can;



// 0 = left 1 = right 
void update_state(DiffState &diffstate, uint8_t move_towards_open, uint8_t move_towards_locked){
    switch (diffstate){
        case ST_OPEN:
            if (move_towards_locked){
                diffstate = ST_SEMI;
                open_to_semi();
            }
        break;

        case ST_SEMI:
            if (move_towards_locked && !move_towards_open){
                diffstate = ST_LOCKED;
                semi_to_locked();
            }
            if (move_towards_open && !move_towards_locked){
                semi_to_open();
            }
        break;

        case ST_LOCKED:
            if (move_towards_open){
                locked_to_semi();
            }
        break;

        case ST_UNKNOWN:
        break;

        default:
        break;
    }
}

void can_callback(const CAN_message_t &msg){
    
}
