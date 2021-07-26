################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Application/DEV_Config/DEV_Config.c \
../Core/Inc/Application/DEV_Config/LORA_Uart.c 

OBJS += \
./Core/Inc/Application/DEV_Config/DEV_Config.o \
./Core/Inc/Application/DEV_Config/LORA_Uart.o 

C_DEPS += \
./Core/Inc/Application/DEV_Config/DEV_Config.d \
./Core/Inc/Application/DEV_Config/LORA_Uart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Application/DEV_Config/DEV_Config.o: ../Core/Inc/Application/DEV_Config/DEV_Config.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/Application/DEV_Config/DEV_Config.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Core/Inc/Application/DEV_Config/DEV_Config.c_includes.args"
Core/Inc/Application/DEV_Config/LORA_Uart.o: ../Core/Inc/Application/DEV_Config/LORA_Uart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/Application/DEV_Config/LORA_Uart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Core/Inc/Application/DEV_Config/LORA_Uart.c_includes.args"

