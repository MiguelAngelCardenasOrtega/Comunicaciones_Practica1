################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_OS_BAREMETAL -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\mdio" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\mmcau" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\phy" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\utilities" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\drivers" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\device" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\component\uart" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\component\lists" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\CMSIS" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\CMSIS_driver" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\board" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\source" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\mdio" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\phy" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\utilities" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\drivers" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\device" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\component\uart" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\component\lists" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\CMSIS" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\CMSIS_driver" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\board" -I"C:\Users\mcardenas\Documents\MCUXpressoIDE_11.6.1_8255\Iteso\frdmk64f_cmsis_enet_txrx_transfer\frdmk64f\cmsis_driver_examples\enet\txrx_transfer" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_assert.d ./utilities/fsl_assert.o ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o

.PHONY: clean-utilities

