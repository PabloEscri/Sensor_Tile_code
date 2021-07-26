################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP_mio/lps22hb/lps22hb.c \
../Drivers/BSP_mio/lps22hb/lps22hb_reg.c 

OBJS += \
./Drivers/BSP_mio/lps22hb/lps22hb.o \
./Drivers/BSP_mio/lps22hb/lps22hb_reg.o 

C_DEPS += \
./Drivers/BSP_mio/lps22hb/lps22hb.d \
./Drivers/BSP_mio/lps22hb/lps22hb_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP_mio/lps22hb/lps22hb.o: ../Drivers/BSP_mio/lps22hb/lps22hb.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP_mio/lps22hb/lps22hb.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Drivers/BSP_mio/lps22hb/lps22hb.c_includes.args"
Drivers/BSP_mio/lps22hb/lps22hb_reg.o: ../Drivers/BSP_mio/lps22hb/lps22hb_reg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/BSP_mio/lps22hb/lps22hb_reg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Drivers/BSP_mio/lps22hb/lps22hb_reg.c_includes.args"

