/*
 * ethernet_layer.h
 *
 *  Created on: Jan 31, 2024
 *      Author: mcardenas
 */

#ifndef ETHERNET_LAYER_H_
#define ETHERNET_LAYER_H_

#include "Driver_ETH_MAC.h"

void ethernet_init(custom_layer_receive_callback cb_event);
uint32_t ethernet_send(uint8_t* data_buffer, uint32_t size);

#endif /* ETHERNET_LAYER_H_ */
