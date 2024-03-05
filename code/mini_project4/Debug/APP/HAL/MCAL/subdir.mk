################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/HAL/MCAL/ICU.c \
../APP/HAL/MCAL/gpio.c 

OBJS += \
./APP/HAL/MCAL/ICU.o \
./APP/HAL/MCAL/gpio.o 

C_DEPS += \
./APP/HAL/MCAL/ICU.d \
./APP/HAL/MCAL/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
APP/HAL/MCAL/%.o: ../APP/HAL/MCAL/%.c APP/HAL/MCAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


