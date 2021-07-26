################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Sensor_Tile_tools/SensorTile_bus.c 

OBJS += \
./Drivers/Sensor_Tile_tools/SensorTile_bus.o 

C_DEPS += \
./Drivers/Sensor_Tile_tools/SensorTile_bus.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Sensor_Tile_tools/SensorTile_bus.o: ../Drivers/Sensor_Tile_tools/SensorTile_bus.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/Sensor_Tile_tools/SensorTile_bus.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Drivers/Sensor_Tile_tools/SensorTile_bus.c_includes.args"

