#ifndef POSITION_H
#define POSITION_H
#include <Arduino.h>
#include "state.h"

#define MOVE_TIMEOUT 4000 // ms - stop the motor if the target isn't reached by then

void stop_motor();
DiffState get_position();

void semi_to_open();
void open_to_semi();

void semi_to_locked();
void locked_to_semi();

#endif //POSITION_H
