#include "sensors.h"
#include "main.h"
#include "MS5837-02BA.h"
#include "communication.h"
#include "stdbool.h"

//extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c2;

bool init_sensors(){
	if (MS5837_02BA_init(&hi2c2)){
		MS5837_02BA_reset_pressure();
	}else{
		return false;
	}
	return true;
}

int32_t get_actual_pressure(){
	return MS5837_02BA_get_actual_pressure();
}

//void HAL_ADC_ConvCpltCallback (ADC_HandleTypeDef *hadc)
//{
//	HAL_ADC_Stop_IT(&hadc1);
//	adcData.results[adcData.conversions] = HAL_ADC_GetValue(&hadc1);
//	adcData.conversions++;
//
//	if(adcData.conversions == ADC_RESULTS_NUMBER) {
//		float temp = 0;
//		for(uint8_t i=0; i<ADC_RESULTS_NUMBER; i++) {
//			temp = temp + ((float) (adcData.results[i]) / 4096 * 3.3);
//			adcData.results[i] = 0;
//		}
//		adcData.average = temp / ADC_RESULTS_NUMBER;
//		adcData.conversions++;
//	}
//	else {
//		HAL_ADC_Start_IT(&hadc1);
//	}
//
//	if(!firsttime) {
//		formData();
//		HAL_I2C_Slave_Transmit_IT(&hi2c1, dataToSend, DATA_TO_SEND_SIZE);
//		firsttime = 1;
//		HAL_IWDG_Init(&hiwdg);
//	}
//}
