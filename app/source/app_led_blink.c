/*******************************************************************************************
 * File name: app_led_blink.c
 * Description: Blinking of LED
 *******************************************************************************************/
#include<stdint.h>
#include "gpio_types.h"
#include "gpio_proto.h"
#include "gpio_macros.h"

gpio_config_t      gpio_pin;
/***********************************************************************************
 * app_led_blink_init.c
 * Initializes the GPIO pins with the respective drivers / lower layer support
 ***********************************************************************************/
void app_led_blink_init(){
	gpio_pin.port_id    = GPIO_ID_A;
	gpio_pin.mode       = GPIO_MODE_OUT;
	gpio_pin.op_type    = GPIO_OP_PUSH_PULL;
	gpio_pin.op_speed   = GPIO_LOW_SPEED;
	gpio_pin.push_pull  = GPIO_PULL_UP;
	gpio_pin.alt_func   = GPIO_AF7;
	gpio_pin.enable     = GPIO_ENABLE;
	gpio_pin.pin_number = 5;
	GPIO_Init(gpio_pin);
}

/***********************************************************************************
 * app_led_blink_update.c
 * Update routine to blink an LED
 ***********************************************************************************/
void app_led_blink_update(uint8_t val,gpio_config_t gpio_pin ){
	GPIO_WritetoPin(gpio_pin,val);
	delay(100000);
	GPIO_WritetoPin(gpio_pin,0);
	delay(100000);
}
