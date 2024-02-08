/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "fsl_mmcau.h"
#include "mmcau_api.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

/*
 * mmcau_encrypt_aes_cbc: AES encryption function
 *
 * Parameters:
 *   [in] key: key of 8 bytes
 *   [in] mode: 128, 192 or 256 AES mode
 *   [in] inputData: pointer to in data
 *   [out] outputData: pointer to out data
 *   [in] dataLength: number of bytes of input data. Must be divisible by 8 (DES block)
 *   [in] initVector: initVector to use during xor
 * Return:
 *   0 if OK, otherwise error
 *
 */
int mmcau_encrypt_aes_cbc(const uint8_t *key,
                                 uint32_t mode,
                                 const uint8_t *inputData,
                                 uint8_t *outputData,
                                 uint16_t dataLength,
                                 const uint8_t *initVector)
{
    uint8_t i;
    uint16_t blocks;
    uint16_t rounds;
    uint8_t tempBlock[AES_BLOCK_LENGTH];
    uint8_t tempIV[AES_BLOCK_LENGTH];
    /*
     * AES128 needs 44 longwords for expansion
     * AES192 needs 52 longwords for expansion
     * AES256 needs 60 longwords for expansion
     *    Reserving 60 longwords as the max space
     */
    uint32_t keyLen;
    uint8_t keyExpansion[60 * 4];

    /*validate NULL for key, inputData, outputData or initVector*/
    if ((key == NULL) || (inputData == NULL) || (outputData == NULL) || (initVector == NULL))
    {
        return MMCAU_ERROR; /*wrong pointer*/
    }

    /*validate AES mode*/
    if ((mode != 128u) && (mode != 192u) && (mode != 256u))
    {
        return MMCAU_ERROR; /*wrong AES mode*/
    }

    /*validate data length*/
    if (dataLength % AES_BLOCK_LENGTH)
    {
        return MMCAU_ERROR; /*wrong length*/
    }

    /*calculate number of AES rounds*/
    if (mode == 128u)
    {
        rounds = 10u;
        keyLen = 16u;
    }
    else if (mode == 192u)
    {
        rounds = 12u;
        keyLen = 24u;
    }
    else /*AES256*/
    {
        rounds = 14u;
        keyLen = 32u;
    }

    /*expand AES key*/
    MMCAU_AES_SetKey(key, keyLen, keyExpansion);

    /*execute AES in CBC mode*/
    /*http://en.wikipedia.org/wiki/Block_cipher_modes_of_operation*/

    /*get number of blocks*/
    blocks = dataLength / AES_BLOCK_LENGTH;

    /*copy init vector to temp storage*/
    memcpy(tempIV, initVector, AES_BLOCK_LENGTH);

    do
    {
        /*copy to temp storage*/
        memcpy(tempBlock, inputData, AES_BLOCK_LENGTH);

        /*xor for CBC*/
        for (i = 0; i < AES_BLOCK_LENGTH; i++)
        {
            tempBlock[i] ^= tempIV[i];
        }

        /*FSL: single AES round*/
        MMCAU_AES_EncryptEcb(tempBlock, keyExpansion, rounds, outputData);

        /*update initVector for next 3DES round*/
        memcpy((void *)tempIV, (void *)outputData, AES_BLOCK_LENGTH);

        /*adjust pointers for next 3DES round*/
        inputData += AES_BLOCK_LENGTH;
        outputData += AES_BLOCK_LENGTH;

    } while (--blocks);

    return MMCAU_OK;
}

/*
 * mmcau_decrypt_aes_cbc: AES decryption function
 *
 * Parameters:
 *   [in] key: key of 8 bytes
 *   [in] mode: 128, 192 or 256 AES mode
 *   [in] inputData: pointer to in data
 *   [out] outputData: pointer to out data
 *   [in] dataLength: number of bytes of input data. Must be divisible by 8 (DES block)
 *   [in] initVector: initVector to use during xor
 * Return:
 *   0 if OK, otherwise error
 *
 */
int mmcau_decrypt_aes_cbc(const uint8_t *key,
                                 uint32_t mode,
                                 const uint8_t *inputData,
                                 uint8_t *outputData,
                                 uint16_t dataLength,
                                 const uint8_t *initVector)
{
    uint8_t i;
    uint16_t blocks;
    uint16_t rounds;
    uint8_t tempBlock[AES_BLOCK_LENGTH];
    uint8_t tempIV[AES_BLOCK_LENGTH];
    /*
     * AES128 needs 44 longwords for expansion
     * AES192 needs 52 longwords for expansion
     * AES256 needs 60 longwords for expansion
     *    Reserving 60 longwords as the max space
     */
    uint8_t keyExpansion[60 * 4];
    uint32_t keyLen;

    /*validate NULL for key, inputData, outputData or initVector*/
    if ((key == NULL) || (inputData == NULL) || (outputData == NULL) || (initVector == NULL))
    {
        return MMCAU_ERROR; /*wrong pointer*/
    }

    /*validate AES mode*/
    if ((mode != 128u) && (mode != 192u) && (mode != 256u))
    {
        return MMCAU_ERROR; /*wrong AES mode*/
    }

    /*validate data length*/
    if (dataLength % AES_BLOCK_LENGTH)
    {
        return MMCAU_ERROR; /*wrong length*/
    }

    /*calculate number of AES rounds*/
    if (mode == 128u)
    {
        rounds = 10u;
        keyLen = 16u;
    }
    else if (mode == 192u)
    {
        rounds = 12u;
        keyLen = 24u;
    }
    else /*AES256*/
    {
        rounds = 14u;
        keyLen = 32u;
    }

    /*expand AES key*/
    MMCAU_AES_SetKey(key, keyLen, keyExpansion);

    /*execute AES in CBC mode*/
    /*http://en.wikipedia.org/wiki/Block_cipher_modes_of_operation*/

    /*get number of blocks*/
    blocks = dataLength / AES_BLOCK_LENGTH;

    /*copy init vector to temp storage*/
    memcpy(tempIV, initVector, AES_BLOCK_LENGTH);

    do
    {
        /*copy to temp storage*/
        memcpy(tempBlock, inputData, AES_BLOCK_LENGTH);

        /*FSL: single AES round*/
        MMCAU_AES_DecryptEcb(inputData, keyExpansion, rounds, outputData);

        /*xor for CBC*/
        for (i = 0; i < AES_BLOCK_LENGTH; i++)
        {
            outputData[i] ^= tempIV[i];
        }

        /*update initVector for next AES round*/
        memcpy(tempIV, tempBlock, AES_BLOCK_LENGTH);

        /*adjust pointers for next 3DES round*/
        inputData += AES_BLOCK_LENGTH;
        outputData += AES_BLOCK_LENGTH;

    } while (--blocks);

    return MMCAU_OK;
}


