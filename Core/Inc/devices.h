/*
 * devices.h
 *
 *  Created on: Mar 28, 2024
 *      Author: Sea Jackal
 */

#ifndef INC_DEVICES_H_
#define INC_DEVICES_H_

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include <stdbool.h>

#define THRUSTER_PWM_MAX 352
#define THRUSTER_PWM_NEUTRAL 480
#define THRUSTER_PWM_MIN 608
#define DEVICES_NUM 2
#define STATES_NUM 2

typedef enum
{
	CLOSED,
	OPENED
} Device_state;

typedef struct {
    TIM_HandleTypeDef *htim;
    uint32_t channel;

    uint16_t state_poses[STATES_NUM];

    Device_state state;
    bool need_update;
} Device_handler;

extern Device_handler devices[DEVICES_NUM];

void init_devices();
void devices_update();
void set_device_state(uint8_t address, Device_state state);

#endif /* INC_DEVICES_H_ */
