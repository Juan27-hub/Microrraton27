/*
 * ades_speedcontrol.h
 *
 *  Created on: Nov 4, 2025
 *      Author: jandr
 */

#ifndef INC_ADES_SPEEDCONTROL_H_
#define INC_ADES_SPEEDCONTROL_H_

#include "main.h"
#include "ades_motordc.h"
#include "ades_odometria.h"

typedef struct{
	float vel_ref;
	float CCRL;
	float CCRR;
	float vel_min;
	float vel_max;
	float vel_ult;
	float i;
	float kP;
	float kI;
	float kD;
} ControlSpeed;

void ades_speedcontrol_configure(ControlSpeed* pid, float KP, float KI, float KD, float valor_objetivo);
void ades_speedcontrol_ajustarPWM(Pose* pose, ControlSpeed* pid);

#endif /* INC_ADES_SPEEDCONTROL_H_ */
