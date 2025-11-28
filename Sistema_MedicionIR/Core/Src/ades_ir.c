/*
 * ades_ir.c
 *
 *  Created on: Oct 20, 2025
 *      Author: jandr
 */

#include "ades_ir.h"

// tx driver

void ades_ir_PowerDownAll(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
}

void ades_ir_PowerDown(uint8_t pin){
	if(pin == 1) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
	if(pin == 2) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);
	if(pin == 3) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
	if(pin == 4) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
}

void ades_ir_PowerUpAll(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
}

void ades_ir_PowerUp(uint8_t pin){
	if(pin == 1) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
	if(pin == 2) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);
	if(pin == 3) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
	if(pin == 4) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
}

//interpolaciones

float interpolacion1(float dato){
	float y;
	float datos1[39] = {1356.0, 1230.0, 980.0, 783.0, 633.0, 494.0, 370.0, 298.0, 230.0, 189.0, 156.0, 128.0, 111.0, 94.0, 82.0, 70.0, 58.0, 50.0, 43.0, 39.89, 33.8, 30.14, 27.6, 23.9, 22.9, 19.7, 18.0, 15.0, 14.0, 12.8, 11.6, 10.6, 9.3, 8.8, 8.1, 7.6, 7.0, 6.2, 5.8};
	if(dato > datos1[0]) y = 5.0;
	for (int i = 1; i < 39; i ++){
		float m = (5.0)/(datos1[i] - datos1[i-1]);
		if (dato < datos1[i-1] && dato > datos1[i]) y = m*(dato - datos1[i-1]) + (float)(i)*5.0;
	}
	if (dato < datos1[38]) y = 200.0;
	return y;
}

float interpolacion2(uint16_t dato){
	float y;
	float datos2[37] = {1043.0, 970.0, 850.0, 743.0, 637.0, 555.0, 481.0, 422.0, 363.0, 322.0, 282.0, 250.0, 224.0, 201.0, 180.0, 162.0, 147.0, 135.0, 124.0, 113.0, 103.0, 94.0, 87.0, 80.0, 74.0, 68.0, 63.0, 58.0, 54.0, 50.0, 46.0, 43.0, 40.0, 37.0, 34.0, 32.0, 30.0};
	for (int i = 1; i < 37; i ++){
		float m = (5.0/(datos2[i-1] - datos2[i]));
		if (dato < datos2[i-1] && dato > datos2[i]) y = m*(dato - datos2[i]) + (float)(i)*5.0;
	}
	if (dato < datos2[36]) y = 200.0;
	return y;
}

float interpolacion3(uint16_t dato){
	float y;
	uint32_t datos3[20];
	if (dato >= datos3[0]) y = 0;
	for (int i = 1; i < 18; i ++){
		if (dato > datos3[i] && dato <= datos3[i-1]) y = (i*0.5) + (-0.5)/(datos3[i-1]-datos3[i])*(dato - datos3[i]);
	}
	if (dato <= datos3[19]) y = 200;
	return y;
}

float interpolacion4(uint16_t dato){
	float y;
	uint32_t datos4[20];
	if (dato >= datos4[0]) y = 0;
	for (int i = 1; i < 18; i ++){
		if (dato > datos4[i] && dato <= datos4[i-1]) y = (i*0.5) + (-0.5)/(datos4[i-1]-datos4[i])*(dato - datos4[i]);
	}
	if (dato <= datos4[19]) y = 200;
	return y;
}

// rx driver


uint16_t ades_ir_ReadADC(uint8_t canal, ADC_HandleTypeDef *hadc){
	uint16_t v_adc;
	v_adc = ADC_SelectCH(hadc, canal);
	return v_adc;
}

float ades_ir_GetDistance(uint8_t pin, float adc){
	float distance = 0;
	if(pin == 1) distance = interpolacion1(adc);
	if(pin == 2) distance = interpolacion2(adc);
	if(pin == 3) distance = interpolacion3(adc);
	if(pin == 4) distance = interpolacion4(adc);

	return distance;
}

void ades_ir_CalculateDistances(Eye* eye, ADC_HandleTypeDef *hadc){
	  uint16_t ADC_RES;
	  float AD_RES;
	  float Prom_ADC;
	  for (int j = 0; j < 4; j++){
		  for (int i = 0; i < 4; i++){
			  ades_ir_PowerDownAll();
			  uint16_t AD_RES1 = ades_ir_ReadADC(ADC_CHANNEL_4, hadc);
			  ades_ir_PowerUp(1);
			  uint16_t AD_RES2 = ades_ir_ReadADC(ADC_CHANNEL_4, hadc);
			  ADC_RES += AD_RES2 - AD_RES1;
			  ades_ir_PowerDownAll();
		  }
		  AD_RES = (float)(ADC_RES)/4.0;
		  Prom_ADC += AD_RES;
		  ADC_RES = 0;
	  }

	  Prom_ADC = Prom_ADC / 4.0;
	  eye->distance_1 = ades_ir_GetDistance(1, Prom_ADC);
	  Prom_ADC = 0.0;

	  for (int j = 0; j < 4; j++){
		  for (int i = 0; i < 4; i++){
			  ades_ir_PowerDownAll();
			  uint16_t AD_RES1 = ades_ir_ReadADC(ADC_CHANNEL_5, hadc);
			  ades_ir_PowerUp(2);
			  uint16_t AD_RES2 = ades_ir_ReadADC(ADC_CHANNEL_5, hadc);
			  ADC_RES += AD_RES2 - AD_RES1;
			  ades_ir_PowerDownAll();
		  }
		  AD_RES = (float)(ADC_RES)/4.0;
		  Prom_ADC += AD_RES;
		  ADC_RES = 0;
	  }

	  Prom_ADC = Prom_ADC / 4.0;
	  eye->distance_2 = ades_ir_GetDistance(1, Prom_ADC);
	  Prom_ADC = 0.0;

	  for (int j = 0; j < 4; j++){
		  for (int i = 0; i < 4; i++){
			  ades_ir_PowerDownAll();
			  uint16_t AD_RES1 = ades_ir_ReadADC(ADC_CHANNEL_6, hadc);
			  ades_ir_PowerUp(3);
			  uint16_t AD_RES2 = ades_ir_ReadADC(ADC_CHANNEL_6, hadc);
			  ADC_RES += AD_RES2 - AD_RES1;
			  ades_ir_PowerDownAll();
		  }
		  AD_RES = (float)(ADC_RES)/4.0;
		  Prom_ADC += AD_RES;
		  ADC_RES = 0;
	  }

	  Prom_ADC = Prom_ADC / 4.0;
	  eye->distance_3 = ades_ir_GetDistance(1, Prom_ADC);
	  Prom_ADC = 0.0;

	  for (int j = 0; j < 4; j++){
		  for (int i = 0; i < 4; i++){
			  ades_ir_PowerDownAll();
			  uint16_t AD_RES1 = ades_ir_ReadADC(ADC_CHANNEL_7, hadc);
			  ades_ir_PowerUp(4);
			  uint16_t AD_RES2 = ades_ir_ReadADC(ADC_CHANNEL_7, hadc);
			  ADC_RES += AD_RES2 - AD_RES1;
			  ades_ir_PowerDownAll();
		  }
		  AD_RES = (float)(ADC_RES)/4.0;
		  Prom_ADC += AD_RES;
		  ADC_RES = 0;
	  }

	  Prom_ADC = Prom_ADC / 4.0;
	  eye->distance_4 = ades_ir_GetDistance(2, Prom_ADC);
	  Prom_ADC = 0.0;

}

