################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/GPIO.c \
../source/LCD_nokia.c \
../source/LCD_nokia_images.c \
../source/Pantalla.c \
../source/SPI.c \
../source/nokia_draw.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/GPIO.d \
./source/LCD_nokia.d \
./source/LCD_nokia_images.d \
./source/Pantalla.d \
./source/SPI.d \
./source/nokia_draw.d \
./source/semihost_hardfault.d 

OBJS += \
./source/GPIO.o \
./source/LCD_nokia.o \
./source/LCD_nokia_images.o \
./source/Pantalla.o \
./source/SPI.o \
./source/nokia_draw.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DFRDM_K64F -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DSDK_OS_FREE_RTOS -DMCUXPRESSO_SDK -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Projects_K64\Sistemas Operativos\Ejercicio_pantalla_freertos_hello\source" -I"C:\Projects_K64\Sistemas Operativos\Ejercicio_pantalla_freertos_hello\drivers" -I"C:\Projects_K64\Sistemas Operativos\Ejercicio_pantalla_freertos_hello\utilities" -I"C:\Projects_K64\Sistemas Operativos\Ejercicio_pantalla_freertos_hello\device" -I"C:\Projects_K64\Sistemas Operativos\Ejercicio_pantalla_freertos_hello\component\uart" -I"C:\Projects_K64\Sistemas Operativos\Ejercicio_pantalla_freertos_hello\component\serial_manager" -I"C:\Projects_K64\Sistemas Operativos\Ejercicio_pantalla_freertos_hello\component\lists" -I"C:\Projects_K64\Sistemas Operativos\Ejercicio_pantalla_freertos_hello\CMSIS" -I"C:\Projects_K64\Sistemas Operativos\Ejercicio_pantalla_freertos_hello\freertos\freertos_kernel\include" -I"C:\Projects_K64\Sistemas Operativos\Ejercicio_pantalla_freertos_hello\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Projects_K64\Sistemas Operativos\Ejercicio_pantalla_freertos_hello\board" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/GPIO.d ./source/GPIO.o ./source/LCD_nokia.d ./source/LCD_nokia.o ./source/LCD_nokia_images.d ./source/LCD_nokia_images.o ./source/Pantalla.d ./source/Pantalla.o ./source/SPI.d ./source/SPI.o ./source/nokia_draw.d ./source/nokia_draw.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

