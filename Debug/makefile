################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include my_FreeRTOS_app/subdir.mk
-include Middlewares/ST/BlueNRG-MS/utils/subdir.mk
-include Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic/subdir.mk
-include Middlewares/ST/BlueNRG-MS/hci/controller/subdir.mk
-include Middlewares/ST/BlueNRG-MS/hci/subdir.mk
-include Middlewares/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/FreeRTOS/Source/subdir.mk
-include Middlewares/FatFs/src/sd_application/subdir.mk
-include Middlewares/FatFs/src/subdir.mk
-include Middlewares/FatFs/JSON/subdir.mk
-include Drivers/Sensor_Tile_tools/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/Legacy/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP_mio/motion_sensors/subdir.mk
-include Drivers/BSP_mio/lsm6dsm/subdir.mk
-include Drivers/BSP_mio/lsm303agr/subdir.mk
-include Drivers/BSP_mio/lps22hb/subdir.mk
-include Drivers/BSP_mio/hts221/subdir.mk
-include Drivers/BSP_mio/Env_sensors_api/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/RTC_APP/subdir.mk
-include Core/Inc/BLE/subdir.mk
-include Core/Inc/Application/L76X/subdir.mk
-include Core/Inc/Application/DEV_Config/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SENSOR_TILE_EXAMP_CON_TAREAS.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SENSOR_TILE_EXAMP_CON_TAREAS.list \

OBJCOPY_BIN += \
SENSOR_TILE_EXAMP_CON_TAREAS.bin \


# All Target
all: SENSOR_TILE_EXAMP_CON_TAREAS.elf secondary-outputs

# Tool invocations
SENSOR_TILE_EXAMP_CON_TAREAS.elf: $(OBJS) $(USER_OBJS) C:\Users\pablo\STM32CubeIDE\workspace_1.4.0\en.stsw-stwinkt01\STSW-STWINKT01_V2.0.0\Projects\BLE_SampleApp\SENSOR_TILE_EXAMP_CON_TAREAS\STM32L476JGYX_FLASH.ld
	arm-none-eabi-gcc -o "SENSOR_TILE_EXAMP_CON_TAREAS.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\pablo\STM32CubeIDE\workspace_1.4.0\en.stsw-stwinkt01\STSW-STWINKT01_V2.0.0\Projects\BLE_SampleApp\SENSOR_TILE_EXAMP_CON_TAREAS\STM32L476JGYX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SENSOR_TILE_EXAMP_CON_TAREAS.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SENSOR_TILE_EXAMP_CON_TAREAS.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SENSOR_TILE_EXAMP_CON_TAREAS.list"
	@echo 'Finished building: $@'
	@echo ' '

SENSOR_TILE_EXAMP_CON_TAREAS.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "SENSOR_TILE_EXAMP_CON_TAREAS.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
