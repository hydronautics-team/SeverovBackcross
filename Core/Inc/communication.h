#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include <stdint.h>
#include "messages.h"
#include <stdbool.h>

//bool parse_normal_package(device_settings *device_struct,  uint8_t  *message);
bool parse_velocity_package(uint8_t  *message);
//bool parse_config_package(device_settings *device_struct,  uint8_t  *message);
void init_comm();
void backplate_uart_handler();
void tx_presure(int32_t int_presure);

//void normal_response();
void device_response();
void update_com();

#endif //__COMMUNICATION_H
