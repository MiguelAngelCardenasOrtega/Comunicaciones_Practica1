/*
 * custom_layer_config.h
 *
 *  Created on: Jan 31, 2024
 *      Author: mcardenas
 */

#ifndef CUSTOM_LAYER_CONFIG_H_
#define CUSTOM_LAYER_CONFIG_H_

#include "mmcau_api.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*16 bytes key: "ultrapassword123"*/
#define AES_KEY {0x75, 0x6c, 0x74, 0x72, 0x61, 0x70, 0x61, 0x73, 0x73, 0x77, 0x6f, 0x72, 0x64, 0x31, 0x32, 0x33}

/*initialization vector: 16 bytes: "mysecretpassword"*/
#define AES_IV  {0x6d, 0x79, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74, 0x70, 0x61, 0x73, 0x73, 0x77, 0x6f, 0x72, 0x64}

#ifndef MAC_ADDRESS
#define MAC_ADDRESS {0xd4, 0xbe, 0xd9, 0x45, 0x22, 0x61}
#endif

#endif /* CUSTOM_LAYER_CONFIG_H_ */
