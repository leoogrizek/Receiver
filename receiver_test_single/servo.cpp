/*
 * servo.cpp
 *
 * Created: 17. 05. 2023 23:30:59
 *  Author: Leo
 */ 

#include "servo.h"
#include <avr/io.h>

// Define and initialize the extern variables here
volatile uint8_t current_channel = 0;
volatile uint16_t pulse_lengths[NUM_CHANNELS] = {0};
uint8_t joystick_values[4] = {0};

// Initialize Timer1 and the output pins
void servo_init() {
	// Set the control pins as outputs
	DDRD |= (1 << THRUST_PIN) | (1 << YAW_PIN) | (1 << PITCH_PIN) | (1 << ROLL_PIN);

	// Initialize Timer1 in CTC mode
	TCCR1B |= (1 << WGM12);
	
	// Start Timer1 with a prescaler of 8
	TCCR1B |= (1 << CS11);

	// Enable the compare match interrupt
	TIMSK1 |= (1 << OCIE1A);
}

// A function to map joystick values to pulse lengths
uint16_t mapJoystickValue(uint8_t value, uint16_t min_pulse, uint16_t max_pulse) {
	return (uint16_t) (2 * ((uint32_t)min_pulse + (((uint32_t)value * (uint32_t)(max_pulse - min_pulse)) / 255))); //cast to uint32_t to avoid overflow

}

uint16_t mapThrustValue(uint8_t value, uint16_t min_pulse, uint16_t max_pulse) {
	if(value <= 140){
		return 2*min_pulse;
	}
	else {
		//map values from 141-255 to min_pulse-max_pulse
		uint16_t new_min = 141;
		uint16_t new_max = 255;

		return (uint16_t) 2*((((uint32_t)(value - new_min) * (uint32_t)(max_pulse - min_pulse)) / (new_max - new_min) + min_pulse)); //cast to uint32_t to avoid overflow
	}
}

// Update the pulse lengths based on the current joystick values
void updatePulseLengths() {
	pulse_lengths[THRUST_CHANNEL] = mapThrustValue(joystick_values[0], 1000, 2000);
	pulse_lengths[YAW_CHANNEL] = mapJoystickValue(joystick_values[1], 500, 2500);
	pulse_lengths[PITCH_CHANNEL] = mapJoystickValue(joystick_values[2], 500, 2500);
	pulse_lengths[ROLL_CHANNEL] = mapJoystickValue(joystick_values[3], 500, 2500);

	// Set the idle time to achieve a total cycle time of 20ms
	pulse_lengths[IDLE_CHANNEL] = 39800 - (pulse_lengths[THRUST_CHANNEL] + pulse_lengths[YAW_CHANNEL] + pulse_lengths[PITCH_CHANNEL] + pulse_lengths[ROLL_CHANNEL]);
}