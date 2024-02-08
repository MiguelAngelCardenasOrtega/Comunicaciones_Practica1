/*
 * mmcau_api.h
 *
 *  Created on: Jan 31, 2024
 *      Author: mcardenas
 */

#ifndef MMCAU_API_H_
#define MMCAU_API_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/


/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*AES specific*/
#define AES128           128
#define AES128_KEY_SIZE  16
#define AES_BLOCK_LENGTH 16

#define AES192          192
#define AES192_KEY_SIZE 24

#define AES256          256
#define AES256_KEY_SIZE 32

/*MMCAU result codes*/
#define MMCAU_OK    0
#define MMCAU_ERROR -1

/*******************************************************************************
 * API
 ******************************************************************************/
int mmcau_encrypt_aes_cbc(const uint8_t *key, uint32_t mode,
                                 const uint8_t *inputData,
                                 uint8_t *outputData,
                                 uint16_t dataLength,
                                 const uint8_t *initVector);

int mmcau_decrypt_aes_cbc(const uint8_t *key,
                                 uint32_t mode,
                                 const uint8_t *inputData,
                                 uint8_t *outputData,
                                 uint16_t dataLength,
                                 const uint8_t *initVector);

#endif /* MMCAU_API_H_ */
