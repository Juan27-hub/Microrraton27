/*
 * ades_ir.h
 *
 *  Created on: Oct 20, 2025
 *      Author: jandr
 */

#ifndef INC_ADES_IR_H_
#define INC_ADES_IR_H_

#include "main.h"
#include "adc_custom.h"

//tx driver


typedef struct {
float distance_1;
float distance_2;
float distance_3;
float distance_4;
}Eye;

void ades_ir_PowerDownAll(void);
void ades_ir_PowerDown(uint8_t);
void ades_ir_PowerUpAll(void);
void ades_ir_PowerUp(uint8_t);

//rx driver

uint16_t ades_ir_ReadADC(uint8_t, ADC_HandleTypeDef* );
float ades_ir_GetDistance(uint8_t, float);
void ades_ir_CalculateDistances(Eye*, ADC_HandleTypeDef *hadc);

#endif /* INC_ADES_IR_H_ */
