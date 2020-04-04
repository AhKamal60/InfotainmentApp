################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECU_Interface/LCD/lcd.c 

OBJS += \
./ECU_Interface/LCD/lcd.o 

C_DEPS += \
./ECU_Interface/LCD/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
ECU_Interface/LCD/%.o: ../ECU_Interface/LCD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


