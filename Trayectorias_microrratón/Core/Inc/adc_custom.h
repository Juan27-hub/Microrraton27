/*
 * acd_custom.h
 *
 *  Created on: Aug 12, 2024
 *      Author: CamiloA
 */

#ifndef INC_ADC_CUSTOM_H_
#define INC_ADC_CUSTOM_H_

#include "main.h"

void ADC_Init_Custom(ADC_HandleTypeDef *use_hadc);
uint32_t ADC_SelectCH(ADC_HandleTypeDef *use_hadc, uint32_t Channel);




#endif /* INC_ADC_CUSTOM_H_ */
