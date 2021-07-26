################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP_mio/motion_sensors/SensorTile_motion_sensors.c 

OBJS += \
./Drivers/BSP_mio/motion_sensors/SensorTile_motion_sensors.o 

C_DEPS += \
./Drivers/BSP_mio/motion_sensors/SensorTile_motion_sensors.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP_mio/motion_sensors/SensorTile_motion_sensors.o: ../Drivers/BSP_mio/motion_sensors/SensorTile_motion_sensors.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP_mio/motion_sensors/SensorTile_motion_sensors.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Drivers/BSP_mio/motion_sensors/SensorTile_motion_sensors.c_includes.args"

