/*******************************************************************************************
 * File name: app_uart_get_data.c
 * Description: The client requests STM32, to send 4 bytes of data stored at a given address
 * Protocol used is described in the readme.text document
 *******************************************************************************************/

#include <stdint.h>
#include "uart_proto.h"
#include "app_uart_proto.h"
extern rx_ready;
extern rx_data;

void app_address_req_init(){
	USART_Init();
}

void app_uart_interrupt(){
	if(rx_ready){
		uint8_t ob = rx_data;
	}
}

void app_address_req_update(){

	uint8_t bytes[4];
	uint32_t address;

	/* receive the request frame ID */
	uint8_t rx_buff = app_req_frame();

	/* if request frame ID == 0x2
	 * Address claim */
	if(rx_buff == 0x2){
		/*send an ACK*/
		app_send_ACK();
		/* get an address from client */
		for(int i=0;i<4;i++){
			bytes[i] = uart_receive();
		}

		/*reconstruct the data*/
		address = bytes[0] | bytes[1]<<8 | bytes[2]<<16 | bytes[3]<<24;
		/* added this part only for testing */
		*((uint8_t*)address + 0) = 1;
		*((uint8_t*)address + 1) = 2;
		*((uint8_t*)address + 2) = 3;
		*((uint8_t*)address + 3) = 4;

		/*send data at the address (sending 4 bytes of data) */
		for(int i=0;i<4;i++)
		{
			uint8_t data = (uint8_t)(*((uint8_t*)address + i));
			uart_write(data);
		}
	}
	else{
		uint8_t data = 0xf;
		uart_write(data);
	}
}
