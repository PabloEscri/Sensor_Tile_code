################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FatFs/src/ccsbcs.c \
../Middlewares/FatFs/src/diskio.c \
../Middlewares/FatFs/src/ff.c \
../Middlewares/FatFs/src/ff_gen_drv.c \
../Middlewares/FatFs/src/syscall.c \
../Middlewares/FatFs/src/unicode.c 

OBJS += \
./Middlewares/FatFs/src/ccsbcs.o \
./Middlewares/FatFs/src/diskio.o \
./Middlewares/FatFs/src/ff.o \
./Middlewares/FatFs/src/ff_gen_drv.o \
./Middlewares/FatFs/src/syscall.o \
./Middlewares/FatFs/src/unicode.o 

C_DEPS += \
./Middlewares/FatFs/src/ccsbcs.d \
./Middlewares/FatFs/src/diskio.d \
./Middlewares/FatFs/src/ff.d \
./Middlewares/FatFs/src/ff_gen_drv.d \
./Middlewares/FatFs/src/syscall.d \
./Middlewares/FatFs/src/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/src/ccsbcs.o: ../Middlewares/FatFs/src/ccsbcs.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FatFs/src/ccsbcs.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Middlewares/FatFs/src/ccsbcs.c_includes.args"
Middlewares/FatFs/src/diskio.o: ../Middlewares/FatFs/src/diskio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FatFs/src/diskio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Middlewares/FatFs/src/diskio.c_includes.args"
Middlewares/FatFs/src/ff.o: ../Middlewares/FatFs/src/ff.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FatFs/src/ff.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Middlewares/FatFs/src/ff.c_includes.args"
Middlewares/FatFs/src/ff_gen_drv.o: ../Middlewares/FatFs/src/ff_gen_drv.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FatFs/src/ff_gen_drv.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Middlewares/FatFs/src/ff_gen_drv.c_includes.args"
Middlewares/FatFs/src/syscall.o: ../Middlewares/FatFs/src/syscall.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FatFs/src/syscall.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Middlewares/FatFs/src/syscall.c_includes.args"
Middlewares/FatFs/src/unicode.o: ../Middlewares/FatFs/src/unicode.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L476xx -DDEBUG -c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FatFs/src/unicode.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" @"Middlewares/FatFs/src/unicode.c_includes.args"

