#ifndef SEVEROV_BACK_PLATE_VMA_THRUSTERS_H
#define SEVEROV_BACK_PLATE_VMA_THRUSTERS_H

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include <stdbool.h>

#define THRUSTER_PWM_MAX 352
#define THRUSTER_PWM_NEUTRAL 480
#define THRUSTER_PWM_MIN 608
#define THRUSTERS_NUM 6

typedef struct {
    uint8_t address;
    TIM_HandleTypeDef *htim;
    uint32_t chanel;
    int8_t velocity;
    bool need_update;
} thruster_t;

void init_thrusters();
void get_thrusters();
void thrusters_update();
void set_thruster_velocity(uint8_t address, int8_t velocity);

#endif //SEVEROV_BACK_PLATE_VMA_THRUSTERS_H
