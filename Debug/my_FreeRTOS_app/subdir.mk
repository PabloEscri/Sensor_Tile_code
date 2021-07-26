################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../my_FreeRTOS_app/my_FreeRTOS_app.c 

OBJS += \
./my_FreeRTOS_app/my_FreeRTOS_app.o 

C_DEPS += \
./my_FreeRTOS_app/my_FreeRTOS_app.d 


# Each subdirectory must supply rules for building sources it contributes
my_FreeRTOS_app/my_FreeRTOS_app.o: ../my_FreeRTOS_app/my_FreeRTOS_app.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"my_FreeRTOS_app/my_FreeRTOS_app.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"my_FreeRTOS_app/my_FreeRTOS_app.c_includes.args"

