#include <avr/io.h>
#include <avr/interrupt.h>


#define F_CPU 16000000UL
#include <util/delay.h>

#include "rf.h"
#include "uart.h"
#include "spi.h"
#include "servo.h"
#include <stdio.h>

// The ISR for Timer1 compare match
ISR(TIMER1_COMPA_vect) {
	// Turn off the current channel
	PORTD &= ~(1 << (current_channel+2)); //+2 bc channel starts with 0 but pins with 2

	// Move to the next channel
	current_channel++;
	if(current_channel >= NUM_CHANNELS) {
		current_channel = 0;
		updatePulseLengths(); // Updating here instead of in the main loop makes sure timings dont get messed up if you change mid cycle
	}

	// Set the pulse length for the next channel
	OCR1A = pulse_lengths[current_channel];

	// Turn on the next channel (unless it's the idle channel)
	if(current_channel != IDLE_CHANNEL) {
		PORTD |= (1 << (current_channel+2));
	}
}

int main(void) {
	uart_init(9600);
	spi_init();
	servo_init();
	sei();
	
	uint8_t RxAddress[] = {0xEE, 0xDD, 0xCC, 0xBB, 0xAA};
	uint8_t RxData[32];
	
	nrf24_init();
	nrf24_set_rx_mode(RxAddress, 10);
	

	uart_println("Beginning ... ");

	char buffer[50];  // Buffer to hold the formatted string
	
	for (int i = 0; i < NUM_CHANNELS; i++) {
		joystick_values[i]=128;
	}
	updatePulseLengths();
	
	while (1) {
		if(nrf24_data_available(1)) {
			nrf24_receive(RxData);
			uart_println("Packet received: ");
			sprintf(buffer, "Thrust: %d, Yaw: %d, Pitch: %d, Roll: %d", pulse_lengths[0], pulse_lengths[1], pulse_lengths[2], pulse_lengths[3]);
			uart_println(buffer);
			uart_newline();
			for (int i = 0; i < NUM_CHANNELS; i++) {
				joystick_values[i]=RxData[i];
			}
			//updatePulseLengths();
		}
		
		//uart_println("test");
	}
}

