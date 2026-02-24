/************************************************************************************
 * File name: app_init.c
 * Initializes all the applications with the respective drivers / lower layer support
 *************************************************************************************/

#include "app_uart_proto.h"
#include "app_gpio_proto.h"
#include "gpio_types.h"

extern gpio_config_t gpio_pin;

void app_init(){
	app_address_req_init();
	//app_led_blink_init();
}

void app_update(){
	app_uart_interrupt();
	//app_address_req_update();
	//app_led_blink_update(1,gpio_pin);
}
