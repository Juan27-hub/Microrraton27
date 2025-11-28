/*
 * ades_usb.c
 *
 *  Created on: Oct 18, 2025
 *      Author: jandr
 */
#include "ades_usb.h"

void ades_usb_tx(float dato1, float dato2, float dato3, float dato4){
	char buffer[50];
	sprintf(buffer,"d1: %.2f d2: %.2f d3: %.2f d4: %.2f\r\n", dato1, dato2, dato3, dato4);
	uint8_t Len = strlen(buffer);
	CDC_Transmit_FS((uint8_t*)buffer, Len);
}


