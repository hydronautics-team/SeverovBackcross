#include <communication.h>
#include <string.h>
#include "checksum.h"
#include "messages.h"
#include "thrusters.h"
#include "main.h"
#include "MS5837-02BA.h"
#include "devices.h"

extern UART_HandleTypeDef huart1;
static uint8_t message_buff[NORMAL_REQUEST_LENGTH];
extern I2C_HandleTypeDef hi2c1;

#define I2C_TX_TIMEOUT 1000
uint32_t hal_last_presure_tick = 0;

uint8_t i2c_master_rx_buff[PRESURE_TX_BUF_SIZE];

HAL_StatusTypeDef status;

enum {
	TRANSMISION,
	NONE,
} i2c_master_tx_state = NONE;

bool frameready = false;
uint32_t watchdog_counter = 0;

enum
{
	WAITING_HEADER,
	RECEIVING_MESSAGE
} uart_state;

bool parse_velocity_package(uint8_t  *message)
{
    if  (IsChecksum8bCorrect(message, NORMAL_REQUEST_LENGTH))  {
    	for(int i = 0; i < THRUSTERS_NUM; i++)
    	{
    		set_thruster_velocity(i, ((struct VelocityRequest*)message)->velocity[i]);
    	}
    	for(int i =0; i<DEVICES_NUM; i++)
    	{
    		set_device_state(i,
    				((struct VelocityRequest*)message)->device_states&(1<<i));
    	}
        return true;
    }
    return false;
}

void init_comm(){
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
}

void AddChecksumm8b(uint8_t *msg, uint16_t length)
{
	uint8_t crc = 0;
	int i = 0;

	for(i=0; i < length - 1; i++) {
		crc ^= msg[i];
	}

	msg[length-1] = crc;
}

void tx_presure(int32_t presure1){
	if (TRANSMISION == i2c_master_tx_state && HAL_GetTick() - hal_last_presure_tick >= I2C_TX_TIMEOUT){
		HAL_I2C_Init(&hi2c1);
		i2c_master_tx_state = NONE;
	}
	if (NONE == i2c_master_tx_state){

		((struct PressureResponse *)i2c_master_rx_buff)->code = PRESSURE_RESPONSE_CODE;
		((struct PressureResponse *)i2c_master_rx_buff)->value = (float)presure1;
		AddChecksumm8b(i2c_master_rx_buff, PRESURE_TX_BUF_SIZE);
		i2c_master_tx_state = TRANSMISION;
		hal_last_presure_tick = HAL_GetTick();
		HAL_I2C_Slave_Transmit_IT(&hi2c1, i2c_master_rx_buff, PRESURE_TX_BUF_SIZE);
	}
}



void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
    if(huart == &huart1){
        HAL_UART_DeInit(&huart1);
        frameready = false;
        HAL_UART_Receive_IT(&huart1, message_buff, NORMAL_REQUEST_LENGTH);
    }
}

void update_com(){
	switch(uart_state)
		{
		case WAITING_HEADER:
			if(message_buff[0]==0xAA)
			{
				uart_state = RECEIVING_MESSAGE;
				status = HAL_UART_Receive(&huart1, &message_buff[1], NORMAL_REQUEST_LENGTH-1, 100);
			}
			else
			{
				status = HAL_UART_Receive(&huart1, message_buff, 1, 100);
			}
			break;
		case RECEIVING_MESSAGE:
			parse_velocity_package(message_buff);
			status = HAL_UART_Receive(&huart1, message_buff, 1, 100);
			uart_state = WAITING_HEADER;
			break;
		}
}

void I2C_SlaveTxCplt(I2C_HandleTypeDef *hi2c){
	i2c_master_tx_state = NONE;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	frameready = true;
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	MS5837_I2C_MasterRxCplt(hi2c);
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	MS5837_I2C_MasterTxCplt(hi2c);
}

void HAL_I2C_MasterErrorCallback(I2C_HandleTypeDef *hi2c) {
	MS5837_I2C_MasterError(hi2c);
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {

}

void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	I2C_SlaveTxCplt(hi2c);
}

void HAL_I2C_SlaveErrorCallback(I2C_HandleTypeDef *hi2c) {

}
