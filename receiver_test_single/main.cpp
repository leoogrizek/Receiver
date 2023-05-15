#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include "rf.h"
#include "uart.h"
#include "spi.h"
#include <stdio.h>

int main(void) {
	uart_init(9600);
	spi_init();
	
	uint8_t RxAddress[] = {0xEE, 0xDD, 0xCC, 0xBB, 0xAA};
	uint8_t RxData[32];
	
	nrf24_init();
	nrf24_set_rx_mode(RxAddress, 10);
	

	uart_println("Beginning ... ");

	char buffer[50];  // Buffer to hold the formatted string
	
	
	while (1) {
		if(nrf24_data_available(1)) {
			nrf24_receive(RxData);
			uart_println("Packet received: ");
			sprintf(buffer, "Thrust: %d, Yaw: %d, Pitch: %d, Roll: %d", RxData[0], RxData[1], RxData[2], RxData[3]);
			uart_println(buffer);
			uart_newline();
			
		}
		
		//uart_println("test");
	}
}
