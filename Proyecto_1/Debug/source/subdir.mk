################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ADC.c \
../source/GPIO.c \
../source/Proyecto_1.c \
../source/pit.c \
../source/semihost_hardfault.c \
../source/thread0.c \
../source/thread1.c \
../source/thread2.c 

C_DEPS += \
./source/ADC.d \
./source/GPIO.d \
./source/Proyecto_1.d \
./source/pit.d \
./source/semihost_hardfault.d \
./source/thread0.d \
./source/thread1.d \
./source/thread2.d 

OBJS += \
./source/ADC.o \
./source/GPIO.o \
./source/Proyecto_1.o \
./source/pit.o \
./source/semihost_hardfault.o \
./source/thread0.o \
./source/thread1.o \
./source/thread2.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\board" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\source" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\utilities" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\drivers" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\device" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\component\serial_manager" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\component\lists" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\CMSIS" -I"C:\Projects_K64\Sistemas Operativos\Proyecto_1\component\uart" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/ADC.d ./source/ADC.o ./source/GPIO.d ./source/GPIO.o ./source/Proyecto_1.d ./source/Proyecto_1.o ./source/pit.d ./source/pit.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/thread0.d ./source/thread0.o ./source/thread1.d ./source/thread1.o ./source/thread2.d ./source/thread2.o

.PHONY: clean-source

