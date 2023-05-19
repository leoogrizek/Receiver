/*
 * servo.h
 *
 * Created: 17. 05. 2023 23:31:14
 *  Author: Leo
 */ 

#include <avr/io.h>

#ifndef SERVO_H_
#define SERVO_H_

#define F_CPU 16000000UL // CPU frequency of 16MHz

// 5 pins to control in total
#define NUM_CHANNELS 5
#define THRUST_CHANNEL 0
#define YAW_CHANNEL 1
#define PITCH_CHANNEL 2
#define ROLL_CHANNEL 3
#define IDLE_CHANNEL 4

// Servo pins, all on PORTD
#define THRUST_PIN PD2
#define YAW_PIN PD3
#define PITCH_PIN PD4
#define ROLL_PIN PD5

// The current channel being pulsed
extern volatile uint8_t current_channel;

// The lengths of the pulses for each channel (in timer counts)
extern volatile uint16_t pulse_lengths[NUM_CHANNELS];

// The joystick values for each control
extern uint8_t joystick_values[4];

void servo_init();
uint16_t mapJoystickValue(uint8_t value, uint16_t min_pulse, uint16_t max_pulse);
void updatePulseLengths();

#endif /* SERVO_H_ */
