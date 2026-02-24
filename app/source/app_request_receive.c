/**************************************************************************
 * File name: app_request_receive.c
 * Description : Defines a function that would process the request data frame
 * which would always be only 1 byte long
 **************************************************************************/

#include <stdint.h>

#define SIZE_OF_REQ_ID 5
uint8_t req_id[SIZE_OF_REQ_ID] = {0x2,0x3,0x4,0x5};

uint8_t app_req_frame(){
	uint8_t rx_buf = uart_receive();
	for(int i=0;i<SIZE_OF_REQ_ID;i++){
		if(rx_buf == req_id[i]){
			return rx_buf;
		}
	}
	return 0;
}

void app_send_ACK(){
	uart_write(0x1);
}

