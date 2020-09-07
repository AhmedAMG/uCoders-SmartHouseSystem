################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../DIO.c \
../INT.c \
../KEYPAD.c \
../LCD.c \
../TIM.c \
../USART.c \
../main.c 

OBJS += \
./ADC.o \
./DIO.o \
./INT.o \
./KEYPAD.o \
./LCD.o \
./TIM.o \
./USART.o \
./main.o 

C_DEPS += \
./ADC.d \
./DIO.d \
./INT.d \
./KEYPAD.d \
./LCD.d \
./TIM.d \
./USART.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


