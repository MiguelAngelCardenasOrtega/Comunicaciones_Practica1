/*
 * custom_layer.c
 *
 *  Created on: Jan 31, 2024
 *      Author: mcardenas
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_crc.h"
#include "custom_layer.h"
#include "ethernet_layer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
uint8_t custom_layer_msg_buffer[MAX_ETH_BUFFER_SIZE] = {0};
uint8_t* input_data = NULL;
const uint8_t g_aesKey128[AES128_KEY_SIZE] = AES_KEY;
const uint8_t g_aesIV[AES_BLOCK_LENGTH] = AES_IV;
const uint8_t macAddr[6] = MAC_ADDRESS;
custom_layer_receive_callback user_callback = NULL;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Init for CRC-16-CCITT.
 * @details Init CRC peripheral module for CRC-16/CCITT-FALSE protocol:
 *          width=16 poly=0x1021 init=0xffff refin=false refout=false xorout=0x0000 check=0x29b1
 *          http://reveng.sourceforge.net/crc-catalogue/
 * name="CRC-16/CCITT-FALSE"
 */
static void InitCrc16_CcittFalse(CRC_Type *base, uint32_t seed)
{
    crc_config_t config;

    /*
     * config.polynomial = 0x1021;
     * config.seed = 0xFFFF;
     * config.reflectIn = false;
     * config.reflectOut = false;
     * config.complementChecksum = false;
     * config.crcBits = kCrcBits16;
     * config.crcResult = kCrcFinalChecksum;
     */
    CRC_GetDefaultConfig(&config);
    config.seed = seed;
    CRC_Init(base, &config);
}

/*!
 * @brief Calculates the CRC-16-CCITT value for a set of data.
 * @param data - pointer to the beginning of the buffer holding the data to calculate the CRC from
 * @param size - Size in bytes of the input data buffer.
 * @return - The calculated CRC-16
 */
static uint16_t calculate_crc(uint8_t* data, uint32_t size)
{
     /* ***************
     * CRC-16/CCITT-FALSE *
     *************** */
	CRC_Type *crc_base = CRC0;
    InitCrc16_CcittFalse(crc_base, 0xFFFFU);
    CRC_WriteData(crc_base, data, size);
    return CRC_Get16bitResult(crc_base);
}

static void add_padding(uint8_t* data, uint32_t size)
{
	uint32_t pad_size = AES_BLOCK_LENGTH - (size % AES_BLOCK_LENGTH);

	for (uint32_t idx = 0; idx < pad_size; idx++)
	{
		data[size + idx] = pad_size;
	}
}

static uint32_t remove_padding(uint8_t* data, uint32_t size)
{
	uint32_t pad_size = data[size - 1];

	if (pad_size == 0)
	{
		pad_size = 16;
	}

	for (uint32_t idx = size - 1; idx >= (size - pad_size); idx--)
	{
		data[idx] = 0;
	}

	return (size - pad_size);
}

/*!
 * @brief Gets a data buffer and sends it trough ethernet according to the custom layer protocol.
 * @param data - pointer to the beginning of the buffer holding the data of the message to be sent
 * @param size - Size in bytes of the input data buffer.
 * @return - CUSTOM_LAYER_OK if successful or an error code otherwise
 */
uint32_t custom_layer_send(uint8_t* data, uint32_t size)
{
	uint32_t ret = CUSTOM_LAYER_OK;

	uint32_t pad_size = AES_BLOCK_LENGTH - (size % AES_BLOCK_LENGTH);

	if ((size + pad_size) > MAX_ETH_BUFFER_SIZE)
	{
		return CUSTOM_LAYER_SIZE_ERROR;
	}

	//Copy the buffer locally
	input_data = (uint8_t*) malloc(size + pad_size);
	memcpy(input_data, data, size);

	//Let's add the padding to the input data to match the AES BLOCK SIZE
	add_padding(input_data, size);

	//Encrypt the data using AES-128
	if (mmcau_encrypt_aes_cbc(g_aesKey128, AES128, input_data, &custom_layer_msg_buffer[0], size + pad_size, g_aesIV) != MMCAU_OK)
	{
		PRINTF("AES-128 CBC encryption failed !\r\n");
		return CUSTOM_LAYER_ERROR;
	}

	//Calculate and add the CRC16
	uint16_t crc = calculate_crc(&custom_layer_msg_buffer[0], size + pad_size);
	memcpy(&custom_layer_msg_buffer[size + pad_size], &crc, sizeof(crc));

	ret = ethernet_send(&custom_layer_msg_buffer[0], size + pad_size + CRC_SIZE);

	free(input_data);

	return ret;
}

void ENET_callback(uint8_t* rx_frame, uint32_t size)
{
	//Will filer the received frames and only process the ones with the same source ADDRESS
	if (memcmp(&rx_frame[6], &macAddr[0], 6U) == 0)
	{
		//Extract the msg size
		uint16_t payload_size = 0;
		memcpy(&payload_size, (uint16_t*) &rx_frame[ETH_LENGTH_OFFSET], sizeof(uint16_t));
		payload_size -= CRC_SIZE;

		//Validate the CRC
        uint16_t crc = calculate_crc(&rx_frame[ETH_PAYLOAD_OFFSET], payload_size);

		if (memcmp(&rx_frame[ETH_PAYLOAD_OFFSET + payload_size], &crc, sizeof(uint16_t)) != 0)
		{
			PRINTF("Invalid Frame, mismatch CRC\r\n");
			return;
		}

		//Decrypt the payload
		uint8_t* recv_msg = (uint8_t*) malloc(payload_size);

		if (mmcau_decrypt_aes_cbc(g_aesKey128, AES128, &rx_frame[ETH_PAYLOAD_OFFSET], recv_msg, payload_size, g_aesIV) != MMCAU_OK)
		{
			PRINTF("AES-128 CBC decryption failed !\r\n");
			free(recv_msg);
			return;
		}

		//Remove the padding
		uint32_t msg_size = remove_padding(recv_msg, payload_size);

		// Call the user receive callback
		if (user_callback != NULL)
		{
			user_callback(recv_msg, msg_size);
		}

		free(recv_msg);
	}
}

void custom_layer_init(custom_layer_receive_callback cb_event)
{
	//initialize the Ethernet stack
	ethernet_init(ENET_callback);

	//set the receive event callback for the user
	user_callback = cb_event;
}


