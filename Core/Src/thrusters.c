#include "thrusters.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

thruster_t thrusters[THRUSTERS_NUM];

int search_thruster_by_address(uint8_t address){
    for(int i = 0; i < THRUSTERS_NUM; i++){
        if(thrusters[i].address == address){
            return i;
        }
    }
}

void set_thruster_velocity(uint8_t address, int8_t velocity){
    int thruster_num = search_thruster_by_address(address);
    thrusters[thruster_num].velocity = velocity;
    thrusters[thruster_num].need_update = true;
}

void thrusters_update(){
    for(int i = 0; i < THRUSTERS_NUM; i++){
        if(thrusters[i].need_update){
            __HAL_TIM_SET_COMPARE(thrusters[i].htim, thrusters[i].chanel, THRUSTER_PWM_NEUTRAL+thrusters[i].velocity);
            thrusters[i].need_update = false;
        }
    }
}

void init_thrusters_data(){
    thrusters[0].address = 0;
    thrusters[0].velocity = 0;
    thrusters[0].htim = &htim1;
    thrusters[0].chanel = TIM_CHANNEL_2;
    thrusters[0].need_update = true;

    thrusters[1].address = 1;
    thrusters[1].velocity = 0;
    thrusters[1].htim = &htim1;
    thrusters[1].chanel = TIM_CHANNEL_3;
    thrusters[1].need_update = true;

    thrusters[2].address = 2;
    thrusters[2].velocity = 0;
    thrusters[2].htim = &htim1;
    thrusters[2].chanel = TIM_CHANNEL_4;
    thrusters[2].need_update = true;

    thrusters[3].address = 3;
    thrusters[3].velocity = 0;
    thrusters[3].htim = &htim2;
    thrusters[3].chanel = TIM_CHANNEL_1;
    thrusters[3].need_update = true;

    thrusters[4].address = 4;
    thrusters[4].velocity = 0;
    thrusters[4].htim = &htim2;
    thrusters[4].chanel = TIM_CHANNEL_2;
    thrusters[4].need_update = true;

    thrusters[5].address = 5;
    thrusters[5].velocity = 0;
    thrusters[5].htim = &htim2;
    thrusters[5].chanel = TIM_CHANNEL_3;
    thrusters[5].need_update = true;
};

void init_thrusters(){
    init_thrusters_data();
    thrusters_update();
    HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_4);

    HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_4);

//    HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
//    HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
//    HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3);
}
