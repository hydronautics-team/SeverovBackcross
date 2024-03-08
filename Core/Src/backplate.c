#include <stdint.h>
#include "backplate.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include <string.h>
#include <stdio.h>
#include "messages.h"
#include <stdbool.h>
#include "checksum.h"
#include "communication.h"
#include "thrusters.h"
#include "sensors.h"
#include "main.h"
#include "MS5837-02BA.h"

extern UART_HandleTypeDef huart1;
extern I2C_HandleTypeDef hi2c1;

int32_t real_depth = 0;
uint32_t dtick;

void backplate_init(){
    init_comm();
    init_thrusters();
 //   init_sensors();
}

void backplate_loop(){
    thrusters_update();
   // tx_presure(MS5837_02BA_get_actual_pressure());

  update_com();

//	uint8_t data[] = {0xAA};
//	HAL_I2C_Slave_Transmit	(&hi2c1, data, 1, HAL_MAX_DELAY);
}
