#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include "rf.h"
#include "uart.h"
#include "spi.h"

uint8_t value = 0;


int main(void) {
	uart_init(9600);
	spi_init();
	
	uint8_t RxAddress[] = {0xEE, 0xDD, 0xCC, 0xBB, 0xAA};
	uint8_t RxData[32];
	
	nrf24_init();
	nrf24_set_rx_mode(RxAddress, 10);
	

	uart_println("Beginning ... ");


	
	
	while (1) {
		if(nrf24_data_available(1)) {
			nrf24_receive(RxData);
			uart_println("Packet received: ");
			uart_println(RxData);
			uart_newline();
			
		}
		_delay_ms(1000);
		//uart_println("test");
	}
}
