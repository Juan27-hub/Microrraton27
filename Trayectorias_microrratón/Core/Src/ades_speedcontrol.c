/*
 * ades_speedcontrol.c
 *
 *  Created on: Nov 4, 2025
 *      Author: jandr
 */

#include "ades_speedcontrol.h"

void ades_speedcontrol_configure(ControlSpeed* pid, float KP, float KI, float KD, float valor_objetivo){
	pid->kP = KP;
	pid->kI = KI;
	pid->kD = KD;
	pid->vel_ref = valor_objetivo;
}

void ades_speedcontrol_ajustarPWM(Pose* pose, ControlSpeed* pid){
	float velL = pose->velMotorL;
	float velR = pose->velMotorR;
	if (velL < 0) velL *= -1;
	if (velR < 0) velR *= -1;
	int32_t errorL = pid->vel_ref - velL;
	int32_t errorR = pid->vel_ref - velR;

	float dIn;
	int32_t ajuste;

	pid->i += pid->kI * (float)errorL;
	dIn = velL - pid->vel_ult;
	ajuste = (pid->kP * (float)errorL) + pid->i - (pid->kD * dIn);
	pid->CCRL = ajuste;

	pid->i += pid->kI * (float)errorR;
	dIn = velR - pid->vel_ult;
	ajuste = (pid->kP * (float)errorR) + pid->i - (pid->kD * dIn);
	pid->CCRR = ajuste;
}

