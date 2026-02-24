/**********************************************************************************
 * File name: app_uart_proto.h
 * Declares the prototype for the application of clinet-server communication via
 * USART , where the client wants data from the server for a given address configuration
 **********************************************************************************/
#include<stdint.h>
/***********************************************************************************
 * app_address_req_init.c
 * Initializes the USART communication application with the respective drivers / lower layer support
 ***********************************************************************************/
void app_address_req_init();

/***********************************************************************************
 * app_address_req_update.c
 * Update routine for the USART communication application
 ***********************************************************************************/
void app_address_req_update();

/***********************************************************************************
 * app_req_frame.c
 * Function to process request frames from client
 ***********************************************************************************/
uint8_t app_req_frame();

/***********************************************************************************
 * app_send_ACK.c
 * Function to send a ACK message to client
 ***********************************************************************************/
void app_send_ACK();
