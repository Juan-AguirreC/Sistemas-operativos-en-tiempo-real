################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/lists/fsl_component_generic_list.c 

C_DEPS += \
./component/lists/fsl_component_generic_list.d 

OBJS += \
./component/lists/fsl_component_generic_list.o 


# Each subdirectory must supply rules for building sources it contributes
component/lists/%.o: ../component/lists/%.c component/lists/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\source" -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\drivers" -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\drivers\freertos" -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\utilities" -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\device" -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\component\uart" -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\component\serial_manager" -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\component\lists" -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\CMSIS" -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\freertos\freertos_kernel\include" -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Projects_K64\Sistemas Operativos\Tarea-3_E1\board" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-component-2f-lists

clean-component-2f-lists:
	-$(RM) ./component/lists/fsl_component_generic_list.d ./component/lists/fsl_component_generic_list.o

.PHONY: clean-component-2f-lists

