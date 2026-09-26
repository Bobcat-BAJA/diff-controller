#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>
#include <FlexCAN_T4.h>

// CAN command: buf[0] != 0 -> step toward open, buf[1] != 0 -> step toward locked
#define DIFF_CAN_ID 0x51

// Motor position sensor pins
#define MOTOR_POSITION1_PIN 0
#define MOTOR_POSITION2_PIN 1
#define MOTOR_POSITION3_PIN 2

// Motor direction pins -- VERIFY ON THE BENCH. If a pair drives the wrong way,
// swap the pin numbers here; nothing else needs to change.
// Drives toward open:   locked -> semi -> open
#define OPEN_CONTROL_PIN1 9
#define OPEN_CONTROL_PIN2 11
// Drives toward locked: open -> semi -> locked
#define LOCK_CONTROL_PIN1 10
#define LOCK_CONTROL_PIN2 12

#include CAN_ID 0x51

extern bool debug_flag;
extern FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can;

#define DEBUG_PRINT(s) do { if (debug_flag) Serial.println(s); } while (0)

void initialize();
#endif // CONFIG_H
