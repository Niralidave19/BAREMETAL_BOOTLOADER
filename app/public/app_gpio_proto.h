/**********************************************************************************
 * File name: app_gpio_proto.h
 * Declares the prototype for the led blinking application
 **********************************************************************************/
#include<stdint.h>
#include "gpio_types.h"
/***********************************************************************************
 * app_led_blink_init.c
 * Initializes the LED Blinking applications with the respective drivers / lower layer support
 ***********************************************************************************/
void app_led_blink_init();

/***********************************************************************************
 * app_led_blink_update.c
 * Update routine, for blinking the LED
 ***********************************************************************************/
void app_led_blink_update(uint8_t val,gpio_config_t gpio_pin);
