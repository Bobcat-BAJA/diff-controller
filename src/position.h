#ifndef POSITION_H
#define POSITION_H
#include <Arduino.h>
#include "state.h"

#define WAIT_TIME 1300

void stop_motor();
void set_control_pins_low();

DiffState get_position(); // State

void semi_to_open();
void open_to_semi();

void semi_to_locked();
void locked_to_semi();

//

#endif //POSITION_H 
