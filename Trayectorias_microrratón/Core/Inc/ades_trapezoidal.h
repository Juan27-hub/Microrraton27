/*
 * ades_trapezoidal.h
 *
 *  Created on: Oct 27, 2025
 *      Author: jandr
 */

#ifndef INC_ADES_TRAPEZOIDAL_H_
#define INC_ADES_TRAPEZOIDAL_H_

#include "main.h"

float ades_trapezoidal_GetDistanceAc (float aceleracion, float v_max);
float ades_trapezoidal_GetDistanceCte (float d_deseada, float d_aceleracion);

float ades_trapezoidal_GetAmplitudeAc (float aceleracion, float val_max);
float ades_trapezoidal_GetAmplitudeCte (float Amp_deseada, float Amp_aceleracion);

#endif /* INC_ADES_TRAPEZOIDAL_H_ */
