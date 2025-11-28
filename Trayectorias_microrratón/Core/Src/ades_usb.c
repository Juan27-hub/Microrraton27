/*
 * ades_usb.c
 *
 *  Created on: Oct 18, 2025
 *      Author: jandr
 */
#include "ades_usb.h"

void ades_usb_tx(float dato){
	char buffer[50];
	sprintf(buffer,"vel_medida: %.2f\r\n", dato);
	uint8_t Len = strlen(buffer);
	CDC_Transmit_FS((uint8_t*)buffer, Len);
}


