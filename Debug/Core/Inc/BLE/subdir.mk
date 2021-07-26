################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/BLE/BLE_APP.c 

OBJS += \
./Core/Inc/BLE/BLE_APP.o 

C_DEPS += \
./Core/Inc/BLE/BLE_APP.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/BLE/BLE_APP.o: ../Core/Inc/BLE/BLE_APP.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/BLE/BLE_APP.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Core/Inc/BLE/BLE_APP.c_includes.args"

