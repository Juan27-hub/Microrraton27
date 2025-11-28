/*
 * ades_trapezoidal.c
 *
 *  Created on: Oct 27, 2025
 *      Author: jandr
 */

#include "ades_trapezoidal.h"

float ades_trapezoidal_GetDistanceAc (float aceleracion, float v_max){
	float d_aceleracion;
	d_aceleracion = (v_max * v_max) / (2.0 * aceleracion);
	return d_aceleracion;
}
float ades_trapezoidal_GetDistanceCte (float d_deseada, float d_aceleracion){
	float d_constante;
	d_constante = d_deseada - (d_aceleracion);
	return d_constante;
}

float ades_trapezoidal_GetAmplitudeAc (float aceleracion, float val_max){
	float amp_aceleracion;
	amp_aceleracion = (val_max * val_max) / (2.0 * aceleracion);
	return amp_aceleracion;
}

float ades_trapezoidal_GetAmplitudeCte (float Amp_deseada, float Amp_aceleracion){
	float amp_constante;
	amp_constante = Amp_deseada - Amp_aceleracion;
	return amp_constante;
}
