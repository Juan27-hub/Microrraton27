/*
 * ades_motordc.h
 *
 *  Created on: Oct 18, 2025
 *      Author: jandr
 */

#ifndef INC_ADES_MOTORDC_H_
#define INC_ADES_MOTORDC_H_

#include "main.h"

float ades_motordc_getpwm(float);
float ades_motordc_getpwm_angular(float);

void ades_motordc_set_motorL(int32_t);
void ades_motordc_set_motorR(int32_t);

#endif /* INC_ADES_MOTORDC_H_ */
