#ifndef STATE_H
#define STATE_H
#include <FlexCAN_T4.h>
#include <stdint.h>

enum DiffState{
    ST_OPEN,
    ST_SEMI,
    ST_LOCKED,
    ST_UNKNOWN
};

void update_state(uint8_t move_towards_open, uint8_t move_towards_locked);
void can_callback(const CAN_message_t &msg);

#endif //STATE_H
