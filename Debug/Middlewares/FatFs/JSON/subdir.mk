################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FatFs/JSON/Parson_Comandos_App.c \
../Middlewares/FatFs/JSON/parson.c 

OBJS += \
./Middlewares/FatFs/JSON/Parson_Comandos_App.o \
./Middlewares/FatFs/JSON/parson.o 

C_DEPS += \
./Middlewares/FatFs/JSON/Parson_Comandos_App.d \
./Middlewares/FatFs/JSON/parson.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/JSON/Parson_Comandos_App.o: ../Middlewares/FatFs/JSON/Parson_Comandos_App.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FatFs/JSON/Parson_Comandos_App.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Middlewares/FatFs/JSON/Parson_Comandos_App.c_includes.args"
Middlewares/FatFs/JSON/parson.o: ../Middlewares/FatFs/JSON/parson.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FatFs/JSON/parson.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Middlewares/FatFs/JSON/parson.c_includes.args"

