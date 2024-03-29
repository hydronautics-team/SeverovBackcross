/*
 * devices.c
 *
 *  Created on: Mar 28, 2024
 *      Author: Sea Jackal
 */

#include "devices.h"

Device_handler devices[DEVICES_NUM];

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void init_devices()
{
	devices[0].htim = &htim3;
	devices[0].channel = TIM_CHANNEL_1;
	devices[0].state_poses[CLOSED] = 600;
	devices[0].state_poses[OPENED] = 350;

	devices[1].htim = &htim3;
	devices[1].channel = TIM_CHANNEL_2;
	devices[1].state_poses[CLOSED] = 480;
	devices[1].state_poses[OPENED] = 200;

	for(uint8_t i = 0; i<DEVICES_NUM; i++)
	{
		devices[i].need_update = true;
		devices[i].state = CLOSED;
		HAL_TIM_PWM_Start_IT(devices[i].htim, devices[i].channel);
	}
}
void devices_update()
{
	for(uint8_t i = 0; i<DEVICES_NUM; i++)
	{
		if(devices[i].need_update)
		{
			__HAL_TIM_SET_COMPARE(devices[i].htim, devices[i].channel,
					devices[i].state_poses[devices[i].state]);
			devices[i].need_update = false;
		}
	}
}
void set_device_state(uint8_t address, Device_state state)
{
	devices[address].need_update = true;
	devices[address].state = state;
}
