################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_crc.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_edma.c \
../drivers/fsl_enet.c \
../drivers/fsl_enet_cmsis.c \
../drivers/fsl_enet_phy_cmsis.c \
../drivers/fsl_ftfx_cache.c \
../drivers/fsl_ftfx_controller.c \
../drivers/fsl_ftfx_flash.c \
../drivers/fsl_ftfx_flexnvm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_sim.c \
../drivers/fsl_smc.c \
../drivers/fsl_sysmpu.c \
../drivers/fsl_uart.c 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_crc.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_edma.d \
./drivers/fsl_enet.d \
./drivers/fsl_enet_cmsis.d \
./drivers/fsl_enet_phy_cmsis.d \
./drivers/fsl_ftfx_cache.d \
./drivers/fsl_ftfx_controller.d \
./drivers/fsl_ftfx_flash.d \
./drivers/fsl_ftfx_flexnvm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_sim.d \
./drivers/fsl_smc.d \
./drivers/fsl_sysmpu.d \
./drivers/fsl_uart.d 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_crc.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_edma.o \
./drivers/fsl_enet.o \
./drivers/fsl_enet_cmsis.o \
./drivers/fsl_enet_phy_cmsis.o \
./drivers/fsl_ftfx_cache.o \
./drivers/fsl_ftfx_controller.o \
./drivers/fsl_ftfx_flash.o \
./drivers/fsl_ftfx_flexnvm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_sim.o \
./drivers/fsl_smc.o \
./drivers/fsl_sysmpu.o \
./drivers/fsl_uart.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_OS_BAREMETAL -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\mdio" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\mmcau" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\phy" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\utilities" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\drivers" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\device" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\component\uart" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\component\lists" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\CMSIS" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\CMSIS_driver" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\board" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\source" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\mdio" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\phy" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\utilities" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\drivers" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\device" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\component\uart" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\component\lists" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\CMSIS" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\CMSIS_driver" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\board" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\frdmk64f\cmsis_driver_examples\enet\txrx_transfer" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_adc16.d ./drivers/fsl_adc16.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_crc.d ./drivers/fsl_crc.o ./drivers/fsl_dmamux.d ./drivers/fsl_dmamux.o ./drivers/fsl_edma.d ./drivers/fsl_edma.o ./drivers/fsl_enet.d ./drivers/fsl_enet.o ./drivers/fsl_enet_cmsis.d ./drivers/fsl_enet_cmsis.o ./drivers/fsl_enet_phy_cmsis.d ./drivers/fsl_enet_phy_cmsis.o ./drivers/fsl_ftfx_cache.d ./drivers/fsl_ftfx_cache.o ./drivers/fsl_ftfx_controller.d ./drivers/fsl_ftfx_controller.o ./drivers/fsl_ftfx_flash.d ./drivers/fsl_ftfx_flash.o ./drivers/fsl_ftfx_flexnvm.d ./drivers/fsl_ftfx_flexnvm.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_i2c.d ./drivers/fsl_i2c.o ./drivers/fsl_sim.d ./drivers/fsl_sim.o ./drivers/fsl_smc.d ./drivers/fsl_smc.o ./drivers/fsl_sysmpu.d ./drivers/fsl_sysmpu.o ./drivers/fsl_uart.d ./drivers/fsl_uart.o

.PHONY: clean-drivers

