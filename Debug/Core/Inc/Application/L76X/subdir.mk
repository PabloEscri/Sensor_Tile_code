################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/Application/L76X/L76X.c 

OBJS += \
./Core/Inc/Application/L76X/L76X.o 

C_DEPS += \
./Core/Inc/Application/L76X/L76X.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/Application/L76X/L76X.o: ../Core/Inc/Application/L76X/L76X.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/Application/L76X/L76X.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Core/Inc/Application/L76X/L76X.c_includes.args"

