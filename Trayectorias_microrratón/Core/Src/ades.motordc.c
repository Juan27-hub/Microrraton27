/*
 * ades.motordc.c
 *
 *  Created on: Oct 18, 2025
 *      Author: jandr
 */

#include "ades_motordc.h"

float ades_motordc_getpwm(float speed){
	float Voltage = ((1.00/181.67) * speed) + 0.258;
	float DutyCycle = Voltage/7.11;
	float ccr = 65535 * DutyCycle;
	return ccr;
}

float ades_motordc_getpwm_angular(float speed){
	float Voltage = ((1.00/29.0) * speed) + 0.258;
	float DutyCycle = Voltage/7.11;
	float ccr = 65535 * DutyCycle;
	return ccr;
}


void ades_motordc_set_motorR(int32_t ccr){
	if (ccr == 0){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	}else if (ccr > 0)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	}else {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
	}
}

void ades_motordc_set_motorL (int32_t ccr){
	if (ccr == 0){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0);
	}else if (ccr > 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
	}else {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, 0);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
	}
}
