#include "position.h"
#include "config.h"
#include "core_pins.h"
#include "state.h"
#include <cstdint>

void stop_motor(){
    digitalWrite(OPEN_CONTROL_PIN1, LOW);
    digitalWrite(OPEN_CONTROL_PIN2, LOW);

    digitalWrite(LOCK_CONTROL_PIN1, LOW);
    digitalWrite(LOCK_CONTROL_PIN2, LOW);
}

//Same function but i feel like naming it stop motor and using it else where is kinda odd
//as the motor isnt necessarily stoped in the process.
void set_control_pins_low(){
    digitalWrite(OPEN_CONTROL_PIN1, LOW);
    digitalWrite(OPEN_CONTROL_PIN2, LOW);

    digitalWrite(LOCK_CONTROL_PIN1, LOW);
    digitalWrite(LOCK_CONTROL_PIN2, LOW);
}

DiffState get_position(){
    uint8_t motor_position1_value = digitalRead(MOTOR_POSITION1_PIN);
    uint8_t motor_position2_value = digitalRead(MOTOR_POSITION2_PIN);
    uint8_t motor_position3_value = digitalRead(MOTOR_POSITION3_PIN);

    if (motor_position1_value == HIGH &&
        motor_position2_value == LOW  &&
        motor_position3_value == LOW ){
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

    return ST_UNKOWN;
}

void locked_to_semi(){
    Serial.println("Diff: LOCKED -> SEMI");
    stop_motor();

    digitalWrite(OPEN_CONTROL_PIN1, HIGH);
    digitalWrite(OPEN_CONTROL_PIN2, HIGH);

    uint32_t start_time = millis();

    while (true){
        uint32_t now = millis();

        if (now - start_time >= WAIT_TIME){
        uint8_t motor_position3_value = digitalRead(MOTOR_POSITION3_PIN);
        uint8_t motor_position2_value = digitalRead(MOTOR_POSITION2_PIN);

        if (motor_position2_value == HIGH &&
            motor_position3_value == HIGH){
            
            stop_motor();

            Serial.println("diff: SEMI");
            return;
            }
        }
    }
}

void semi_to_locked(){
    Serial.println("diff: SEMI -> LOCKED");
    stop_motor();

    digitalWrite(LOCK_CONTROL_PIN1, HIGH);
    digitalWrite(LOCK_CONTROL_PIN2, HIGH);

    uint32_t start_time = millis();

    while (true){
        uint32_t now = millis();
        if (now - start_time >= WAIT_TIME){
        uint8_t motor_position1_value = digitalRead(MOTOR_POSITION1_PIN);
        uint8_t motor_position2_value = digitalRead(MOTOR_POSITION2_PIN);
        uint8_t motor_position3_value = digitalRead(MOTOR_POSITION3_PIN);
        
        if (motor_position1_value == HIGH && 
            motor_position2_value == HIGH && 
            motor_position3_value == LOW){
                stop_motor();
                Serial.println("diff: LOCKED");
                return;
            }
        }
    }
}

void semi_to_open(){
    Serial.println("diff: SEMI -> OPEN");
    stop_motor();

    digitalWrite(OPEN_CONTROL_PIN1, HIGH);
    digitalWrite(OPEN_CONTROL_PIN2, HIGH);

    uint32_t start_time = millis();
    
    while (true){
        uint32_t now = millis();
        if (now - start_time >= WAIT_TIME){

            uint8_t motor_position1_value = digitalRead(MOTOR_POSITION1_PIN);
            uint8_t motor_position2_value = digitalRead(MOTOR_POSITION2_PIN);
            uint8_t motor_position3_value = digitalRead(MOTOR_POSITION3_PIN);

            if (motor_position1_value == HIGH &&
                motor_position2_value == LOW  &&
                motor_position3_value == LOW ){
                    stop_motor();
                    Serial.println("diff: OPEN");
                    return;
            }
        }
    }
}

void open_to_semi(){
    Serial.println("diff OPEN -> SEMI");
    stop_motor();
    
    digitalWrite(LOCK_CONTROL_PIN1, HIGH);
    digitalWrite(LOCK_CONTROL_PIN2, HIGH);

    uint32_t start_time = millis();

    while (true){
        uint32_t now = millis();
        if (now - start_time >= WAIT_TIME){
            uint8_t motor_position2_value = digitalRead(MOTOR_POSITION2_PIN);
            uint8_t motor_position3_value = digitalRead(MOTOR_POSITION3_PIN);
            
            if (motor_position2_value == HIGH &&
                motor_position3_value == HIGH){
                stop_motor();
                Serial.println("diff: SEMI");
                return;
            }
        }
    }
}



