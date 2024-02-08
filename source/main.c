/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */
#include <string.h>
#include <stdio.h>
/*  SDK Included Files */
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "stdlib.h"
#include "fsl_common.h"
#include "fsl_sysmpu.h"
#include "custom_layer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void user_receive_callback(uint8_t* rx_frame, uint32_t size)
{
	PRINTF("Received Ethernet Frame -> size:%u\r\n", size);

	PRINTF("%s\r\n\r\n", rx_frame);
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Hardware Initialization. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Disable SYSMPU. */
    SYSMPU_Enable(SYSMPU, false);

    PRINTF("\r\nCustom Protocol Layer start.\r\n");

    uint8_t msg[1500] = {0};
    uint32_t idx= 0;
    uint8_t ch = 0;

    custom_layer_init(user_receive_callback);

    while (1)
    {
    	PRINTF("Enter the message to be transmitted: \r\n");
    	ch = GETCHAR();

    	while (ch != '\n')
    	{
    		msg[idx] = ch;
    		idx++;

			ch = GETCHAR();
    	}

		custom_layer_send(msg, idx);

		memset(msg, 0, sizeof(msg));
		idx = 0;
    }
}

