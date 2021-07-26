################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP_mio/lsm303agr/lsm303agr.c \
../Drivers/BSP_mio/lsm303agr/lsm303agr_reg.c 

OBJS += \
./Drivers/BSP_mio/lsm303agr/lsm303agr.o \
./Drivers/BSP_mio/lsm303agr/lsm303agr_reg.o 

C_DEPS += \
./Drivers/BSP_mio/lsm303agr/lsm303agr.d \
./Drivers/BSP_mio/lsm303agr/lsm303agr_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP_mio/lsm303agr/lsm303agr.o: ../Drivers/BSP_mio/lsm303agr/lsm303agr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP_mio/lsm303agr/lsm303agr.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Drivers/BSP_mio/lsm303agr/lsm303agr.c_includes.args"
Drivers/BSP_mio/lsm303agr/lsm303agr_reg.o: ../Drivers/BSP_mio/lsm303agr/lsm303agr_reg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP_mio/lsm303agr/lsm303agr_reg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Drivers/BSP_mio/lsm303agr/lsm303agr_reg.c_includes.args"

