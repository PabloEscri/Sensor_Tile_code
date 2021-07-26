################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/RTC_APP/RTC_APP.c 

OBJS += \
./Core/RTC_APP/RTC_APP.o 

C_DEPS += \
./Core/RTC_APP/RTC_APP.d 


# Each subdirectory must supply rules for building sources it contributes
Core/RTC_APP/RTC_APP.o: ../Core/RTC_APP/RTC_APP.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/RTC_APP/RTC_APP.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Core/RTC_APP/RTC_APP.c_includes.args"

