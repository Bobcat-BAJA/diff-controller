#ifndef CONFIG_H
#define CONFIG_H

//Motor Position Pins
#define MOTOR_POSITION1_PIN 0
#define MOTOR_POSITION2_PIN 1
#define MOTOR_POSITION3_PIN 2

//Motor Directions Pins
//Moves towards locked state open -> semi -> locked
#define OPEN_CONTROL_PIN1 9
#define OPEN_CONTROL_PIN2 11

//Moves towards open state locked -> semi -> open
#define LOCK_CONTROL_PIN1 10
#define LOCK_CONTROL_PIN2 12

extern bool debug_flag;
void initalize();
#endif //CONFIG_H
