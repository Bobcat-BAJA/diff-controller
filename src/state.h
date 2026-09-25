#ifndef STATE_H
#define STATE_H
#include <FlexCAN_T4.h>
#include "stdint.h"

enum DiffState{
    ST_OPEN,
    ST_SEMI,
    ST_LOCKED,
    ST_UNKNOWN
};

void update_state(DiffState &diffstate, uint8_t move_toward_open, uint8_t move_toward_locked);
void can_callback(const CAN_message_t &msg);

#endif //STATE_H
