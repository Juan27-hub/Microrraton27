/*
 * ades_usb.h
 *
 *  Created on: Oct 18, 2025
 *      Author: jandr
 */

#ifndef INC_ADES_USB_H_
#define INC_ADES_USB_H_

#include "main.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

void ades_usb_rx(void);
void ades_usb_tx(float, float, float, float);

#endif /* INC_ADES_USB_H_ */

