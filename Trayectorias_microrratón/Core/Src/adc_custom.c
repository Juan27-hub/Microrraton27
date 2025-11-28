/*
 * adc_custom.c
 *
 *  Created on: Aug 12, 2024
 *      Author: CamiloA
 */
#include "main.h"
#include "adc_custom.h"

void ADC_Init_Custom(ADC_HandleTypeDef *use_hadc){


	use_hadc->Instance = ADC1;
	use_hadc->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	use_hadc->Init.Resolution = ADC_RESOLUTION_12B;
	use_hadc->Init.ScanConvMode = DISABLE;
	use_hadc->Init.ContinuousConvMode = DISABLE;
	use_hadc->Init.DiscontinuousConvMode = DISABLE;
	use_hadc->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	use_hadc->Init.ExternalTrigConv = ADC_SOFTWARE_START;
	use_hadc->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	use_hadc->Init.NbrOfConversion = 1;
	use_hadc->Init.DMAContinuousRequests = DISABLE;
	use_hadc->Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	   if (HAL_ADC_Init(use_hadc) != HAL_OK)
	   {
	     Error_Handler();
	   }
}

//Parametro para seleccionar el canal:
//ADC_CHANNEL_0
uint32_t ADC_SelectCH(ADC_HandleTypeDef *use_hadc, uint32_t Channel){

	ADC_ChannelConfTypeDef sConfig = {0};
	uint32_t result;

	sConfig.Channel = Channel;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(use_hadc, &sConfig) != HAL_OK)
	{
	Error_Handler();
	}

	HAL_ADC_Start(use_hadc);
	HAL_ADC_PollForConversion(use_hadc, HAL_MAX_DELAY);
	result= HAL_ADC_GetValue(use_hadc);
	HAL_ADC_Stop(use_hadc);
	return result;
}
