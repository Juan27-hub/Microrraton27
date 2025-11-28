/*
 * ades_movimiento.c
 *
 *  Created on: Nov 4, 2025
 *      Author: jandr
 */

#include "ades_movimiento.h"

void ades_movimiento_lineal(float distance, float vel_max, float aceleracion, Pose * pose, Move * move, ControlSpeed * pid){
   	float d_aceleracion = ades_trapezoidal_GetDistanceAc(aceleracion, vel_max);
   	float d_constante = ades_trapezoidal_GetDistanceCte(distance , d_aceleracion);
   	move->time_s = 0;
   	pid->vel_ref = vel_max;

   	TIM5->CNT = 0;

	while (pose->velLineal < vel_max){
		uint32_t ccr_value = ades_motordc_getpwm(aceleracion * (float)(TIM5->CNT/1000000));
		ades_motordc_set_motorL(ccr_value);
		ades_motordc_set_motorR(ccr_value);
		TIM3->CCR2 = ccr_value;
		TIM10->CCR1 = ccr_value;
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
	}

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);

	while (pose->avanceLineal <= d_constante){
		//ades_speedcontrol_ajustarPWM(pose, pid);
		//uint32_t ccr_bruto = ades_motordc_getpwm(pid->vel_ref);
		//TIM3->CCR2 = ccr_bruto; //+ pid->CCRL;
		//TIM10->CCR1 = ccr_bruto; //+ pid->CCRR;
	}

	TIM5->CNT = 0;

	float velocidad = pose->velLineal;

	while (pose->velLineal > 0.0){
		move->time_s = TIM5->CNT;
		uint32_t ccr_value = ades_motordc_getpwm(velocidad - aceleracion * (float)(move->time_s/1000000));
		TIM3->CCR2 = ccr_value;
		TIM10->CCR1 = ccr_value;
		ades_motordc_set_motorL(ccr_value);
		ades_motordc_set_motorR(ccr_value);
		move->desacelera = 1;
	}
	ades_motordc_set_motorL(0);
	ades_motordc_set_motorR(0);

	move->time_s = 0;
	ades_odometria_reset(pose);
}

void ades_movimiento_angular(float amplitud, float vel_max, float aceleracion, Pose * pose, Move * move, ControlSpeed * pid){
   	float Am_aceleracion = ades_trapezoidal_GetAmplitudeAc(aceleracion, vel_max);
   	float Am_constante = ades_trapezoidal_GetAmplitudeCte(amplitud , Am_aceleracion);
   	move->time_s = 0;
   	pid->vel_ref = vel_max;

   	TIM5->CNT = 0;

	while (pose->velAngular < vel_max){
		uint32_t ccr_value = ades_motordc_getpwm_angular(aceleracion * (float)(TIM5->CNT/1000000));
		ades_motordc_set_motorL((int32_t)(-1 * ccr_value));
		ades_motordc_set_motorR(ccr_value);
		TIM3->CCR2 =  ccr_value;
		TIM10->CCR1 = ccr_value;
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
	}

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);

	while (pose->theta <= Am_constante){
		//ades_speedcontrol_ajustarPWM(pose, pid);
		//uint32_t ccr_bruto = ades_motordc_getpwm(pid->vel_ref);
		//TIM3->CCR2 = ccr_bruto; //+ pid->CCRL;
		//TIM10->CCR1 = ccr_bruto; //+ pid->CCRR;
	}

	TIM5->CNT = 0;

	float velocidad = pose->velAngular;

	while (pose->velAngular > 0.0){
		move->time_s = TIM5->CNT;
		uint32_t ccr_value = ades_motordc_getpwm(velocidad - aceleracion * (float)(move->time_s/1000000));
		TIM3->CCR2 = ccr_value;
		TIM10->CCR1 = ccr_value;
		ades_motordc_set_motorL((int32_t)(-1 * ccr_value));
		ades_motordc_set_motorR(ccr_value);
		move->desacelera = 1;
	}
	ades_motordc_set_motorL(0);
	ades_motordc_set_motorR(0);

	move->time_s = 0;
	ades_odometria_reset(pose);
}
