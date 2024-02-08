/*
 * custom_layer.h
 *
 *  Created on: Jan 31, 2024
 *      Author: mcardenas
 */

#ifndef CUSTOM_LAYER_H_
#define CUSTOM_LAYER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "custom_layer_config.h"
#include "mmcau_api.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum
{
    CUSTOM_LAYER_OK = 0,
    CUSTOM_LAYER_ERROR,
	CUSTOM_LAYER_SIZE_ERROR,
} custom_layer_errors;

typedef void (*custom_layer_receive_callback) (uint8_t* rx_frame, uint32_t size);

#define MAX_MSG_BUFFER_SIZE (1488U) //This is the biggest number divisible by 16 that can fit the the MAX ethernet payload size of 1500 bytes
#define MAX_ETH_BUFFER_SIZE (1500U)
#define CRC_SIZE			(2U)
#define ETH_HEADER_SIZE	    (14U)
#define ETH_PAYLOAD_OFFSET	(14U)
#define ETH_LENGTH_OFFSET	(12U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void custom_layer_init(custom_layer_receive_callback cb_event);
uint32_t custom_layer_send(uint8_t* data, uint32_t size);

#endif /* CUSTOM_LAYER_H_ */
