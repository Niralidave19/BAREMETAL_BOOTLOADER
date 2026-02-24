/**********************************************************************************
 * File name: app_proto.h
 * Declare all the prototypes for the application layer
 * (app_init() and app_update())
 **********************************************************************************/

/***********************************************************************************
 * app_init.c
 * Initializes all the applications with the respective drivers / lower layer support
 ***********************************************************************************/
void app_init();

/***********************************************************************************
 * app_update.c
 * Update routine of all the apps called here
 ***********************************************************************************/
void app_update();

void check_receive();
