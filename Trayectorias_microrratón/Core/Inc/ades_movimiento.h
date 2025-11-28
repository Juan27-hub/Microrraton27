/*
 * ades_movimiento.h
 *
 *  Created on: Nov 4, 2025
 *      Author: jandr
 */

#ifndef INC_ADES_MOVIMIENTO_H_
#define INC_ADES_MOVIMIENTO_H_

#include "main.h"
#include "ades_trapezoidal.h"
#include "ades_motordc.h"
#include "ades_odometria.h"
#include "ades_speedcontrol.h"

typedef struct{

	uint8_t acelera;
	uint8_t mantenga;
	uint8_t desacelera;
	uint32_t time_s;
	float vel_chida;

} Move;

void ades_movimiento_lineal(float distance, float vel_max, float aceleracion, Pose * pose, Move * move, ControlSpeed * pid);

void ades_movimiento_angular(float amplitud, float vel_max, float aceleracion, Pose * pose, Move * move, ControlSpeed * pid);

#endif /* INC_ADES_MOVIMIENTO_H_ */
