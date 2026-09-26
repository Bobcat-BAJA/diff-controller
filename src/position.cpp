#include "position.h"
#include "config.h"

void stop_motor(){
    digitalWrite(OPEN_CONTROL_PIN1, LOW);
    digitalWrite(OPEN_CONTROL_PIN2, LOW);

    digitalWrite(LOCK_CONTROL_PIN1, LOW);
    digitalWrite(LOCK_CONTROL_PIN2, LOW);
}

void drive_towards_open(){
    stop_motor();
    digitalWrite(OPEN_CONTROL_PIN1, HIGH);
    digitalWrite(OPEN_CONTROL_PIN2, HIGH);
}

void drive_towards_locked(){
    stop_motor();
    digitalWrite(LOCK_CONTROL_PIN1, HIGH);
    digitalWrite(LOCK_CONTROL_PIN2, HIGH);
}

DiffState get_position(){
    uint8_t motor_position1_value = digitalRead(MOTOR_POSITION1_PIN);
    uint8_t motor_position2_value = digitalRead(MOTOR_POSITION2_PIN);
    uint8_t motor_position3_value = digitalRead(MOTOR_POSITION3_PIN);

    if (motor_position1_value == HIGH &&
        motor_position2_value == LOW  &&
        motor_position3_value == LOW){
        return ST_OPEN;
    }

    if (motor_position2_value == HIGH &&
        motor_position3_value == HIGH){
        return ST_SEMI;
    }

    if (motor_position1_value == HIGH &&
        motor_position2_value == HIGH &&
        motor_position3_value == LOW){
        return ST_LOCKED;
    }

    return ST_UNKNOWN;
}

// Keep the motor running until the diff reaches target, or give up after MOVE_TIMEOUT
void wait_for(DiffState target){
    uint32_t start_time = millis();

    while (millis() - start_time < MOVE_TIMEOUT){
        if (get_position() == target){
            stop_motor();
            DEBUG_PRINT("diff: done");
            return;
        }
    }

    stop_motor();
    DEBUG_PRINT("diff: FAULT - move timed out");
}

void locked_to_semi(){
    DEBUG_PRINT("diff: LOCKED -> SEMI");
    drive_towards_open();
    wait_for(ST_SEMI);
}

void semi_to_locked(){
    DEBUG_PRINT("diff: SEMI -> LOCKED");
    drive_towards_locked();
    wait_for(ST_LOCKED);
}

void semi_to_open(){
    DEBUG_PRINT("diff: SEMI -> OPEN");
    drive_towards_open();
    wait_for(ST_OPEN);
}

void open_to_semi(){
    DEBUG_PRINT("diff: OPEN -> SEMI");
    drive_towards_locked();
    wait_for(ST_SEMI);
}
