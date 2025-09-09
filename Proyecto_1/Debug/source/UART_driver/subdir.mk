################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/UART_driver/UART_driver.c 

C_DEPS += \
./source/UART_driver/UART_driver.d 

OBJS += \
./source/UART_driver/UART_driver.o 


# Each subdirectory must supply rules for building sources it contributes
source/UART_driver/%.o: ../source/UART_driver/%.c source/UART_driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\board" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\source" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\utilities" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\drivers" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\device" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\component\serial_manager" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\component\lists" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\CMSIS" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\component\uart" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-UART_driver

clean-source-2f-UART_driver:
	-$(RM) ./source/UART_driver/UART_driver.d ./source/UART_driver/UART_driver.o

.PHONY: clean-source-2f-UART_driver

