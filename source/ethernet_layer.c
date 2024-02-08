/*
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */
#include <string.h>
/*  SDK Included Files */
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_enet.h"
#include "fsl_enet_cmsis.h"
#include "fsl_enet_phy_cmsis.h"
#include "fsl_phy.h"
#include "fsl_common.h"
#include "fsl_phyksz8081.h"
#include "fsl_enet_mdio.h"
#include "RTE_Device.h"
#include "custom_layer.h"
#include "ethernet_layer.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* ENET base address */
#define EXAMPLE_ENET     Driver_ETH_MAC0
#define EXAMPLE_ENET_PHY Driver_ETH_PHY0
#define ENET_DATA_LENGTH        (1500U)
#define ENET_EXAMPLE_LOOP_COUNT (20U)
#define ENET_HEADER_SIZE	    (14U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
const uint8_t g_macAddr[6] = MAC_ADDRESS;
uint8_t tx_frame[ENET_DATA_LENGTH + ENET_HEADER_SIZE];
uint8_t rx_frame[ENET_DATA_LENGTH + ENET_HEADER_SIZE];
custom_layer_receive_callback receive_callback = NULL;

/*******************************************************************************
 * Code
 ******************************************************************************/
mdio_handle_t mdioHandle = {.ops = &enet_ops};
phy_handle_t phyHandle   = {.phyAddr = RTE_ENET_PHY_ADDRESS, .mdioHandle = &mdioHandle, .ops = &phyksz8081_ops};

uint32_t ENET0_GetFreq(void)
{
    return CLOCK_GetFreq(kCLOCK_CoreSysClk);
}

void ENET_SignalEvent_t(uint32_t event)
{
    if (event == ARM_ETH_MAC_EVENT_RX_FRAME)
    {
        uint32_t size;
        uint32_t len;

        // Get the Frame size
        size = EXAMPLE_ENET.GetRxFrameSize();
        // Call ENET_ReadFrame when there is a received frame.
        if (size != 0)
        {
            // Received valid frame. Deliver the rx buffer with the size equal to length.
			len = EXAMPLE_ENET.ReadFrame(rx_frame, size);
			if (size == len)
			{
				// Call the custom layer callback
				if (receive_callback != NULL)
				{
					receive_callback(rx_frame, size);
				}
			}
        }
    }
}

/*! @brief Build Ethernet Frame for transmit. */
static void ENET_BuildBroadCastFrame(uint8_t* data_buffer, uint32_t size)
{
    uint32_t count  = 0;

    //Fill the destination address as a broadcast frame
    for (count = 0; count < 6; count++)
	{
    	tx_frame[count] = 0xFFU;
	}

    //Copy the device's MAC address in the src address field
    memcpy(&tx_frame[6], &g_macAddr[0], 6U);

    //Fill the length field of the frame
    memcpy((uint16_t*) &tx_frame[12],(uint16_t*) &size, sizeof(uint16_t));

    //Copy the passed data from the custom layer to the frame
    memcpy(&tx_frame[14], data_buffer, size);
}

/*!
 * @brief Function to initialize the ENET driver, the Ethernet PHY and the callback functions
 */
void ethernet_init(custom_layer_receive_callback cb_event)
{
    ARM_ETH_LINK_INFO linkInfo;

    mdioHandle.resource.base        = ENET;
    mdioHandle.resource.csrClock_Hz = ENET0_GetFreq();

    //set the receive event callback for the custom layer
    receive_callback = cb_event;

    /* Initialize the ENET module. */
    EXAMPLE_ENET.Initialize(ENET_SignalEvent_t);
    EXAMPLE_ENET.PowerControl(ARM_POWER_FULL);
    EXAMPLE_ENET.SetMacAddress((ARM_ETH_MAC_ADDR *)g_macAddr);

    PRINTF("Wait for PHY init...\r\n");
    while (EXAMPLE_ENET_PHY.PowerControl(ARM_POWER_FULL) != ARM_DRIVER_OK)
    {
        PRINTF("PHY Auto-negotiation failed, please check the cable connection and link partner setting.\r\n");
    }

    EXAMPLE_ENET.Control(ARM_ETH_MAC_CONTROL_RX, 1);
    EXAMPLE_ENET.Control(ARM_ETH_MAC_CONTROL_TX, 1);
    PRINTF("Wait for PHY link up...\r\n");
    do
    {
        if (EXAMPLE_ENET_PHY.GetLinkState() == ARM_ETH_LINK_UP)
        {
            linkInfo = EXAMPLE_ENET_PHY.GetLinkInfo();
            EXAMPLE_ENET.Control(ARM_ETH_MAC_CONFIGURE, linkInfo.speed << ARM_ETH_MAC_SPEED_Pos |
                                                            linkInfo.duplex << ARM_ETH_MAC_DUPLEX_Pos |
                                                            ARM_ETH_MAC_ADDRESS_BROADCAST);
            break;
        }
    } while (1);
}

uint32_t ethernet_send(uint8_t* data_buffer, uint32_t size)
{
	ENET_BuildBroadCastFrame(data_buffer, size);

	uint32_t ret = EXAMPLE_ENET.SendFrame(tx_frame, size + ENET_HEADER_SIZE, ARM_ETH_MAC_TX_FRAME_EVENT);

	if (ret == ARM_DRIVER_OK)
	{
		PRINTF(" \r\nFrame Transmitted!\r\n");
	}
	else
	{
		PRINTF(" \r\nTransmit frame failed!\r\n");
	}

	return ret;
}
