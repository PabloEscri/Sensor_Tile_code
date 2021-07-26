################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32l476jgyx.s 

OBJS += \
./Core/Startup/startup_stm32l476jgyx.o 

S_DEPS += \
./Core/Startup/startup_stm32l476jgyx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/startup_stm32l476jgyx.o: ../Core/Startup/startup_stm32l476jgyx.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I"C:/Users/pablo/STM32CubeIDE/workspace_1.4.0/en.stsw-stwinkt01/STSW-STWINKT01_V2.0.0/Projects/BLE_SampleApp/SENSOR_TILE_EXAMP/Drivers/BSP_mio/lps22hb" -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32l476jgyx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

