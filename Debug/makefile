################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include USB_DEVICE/Target/subdir.mk
-include USB_DEVICE/App/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/display/Font/subdir.mk
-include Core/display/subdir.mk
-include Core/core/src/subdir.mk
-include Core/Src/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := cmsis_fft_dsp_f7
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
cmsis_fft_dsp_f7.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
cmsis_fft_dsp_f7.list \

OBJCOPY_HEX += \
cmsis_fft_dsp_f7.hex \

OBJCOPY_BIN += \
cmsis_fft_dsp_f7.bin \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: cmsis_fft_dsp_f7.elf secondary-outputs

# Tool invocations
cmsis_fft_dsp_f7.elf: $(OBJS) $(USER_OBJS) C:\Users\flegler.a\Desktop\Work_space\git_clone\spectrumAnalizer\STM32F767ZI_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "cmsis_fft_dsp_f7.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\flegler.a\Desktop\Work_space\git_clone\spectrumAnalizer\STM32F767ZI_FLASH.ld" --specs=nosys.specs -Wl,-Map="cmsis_fft_dsp_f7.map" -Wl,--gc-sections -static -Wl,--start-group -larm_cortexM7lfdp_math -Wl,--end-group -L"C:\Users\flegler.a\Desktop\Work_space\git_clone\spectrumAnalizer\Drivers\CMSIS\GCC" -Wl,-cref,-u,Reset_Handler,-u,_scanf_float,-u,_printf_float,-u,vfprintf --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

cmsis_fft_dsp_f7.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "cmsis_fft_dsp_f7.list"
	@echo 'Finished building: $@'
	@echo ' '

cmsis_fft_dsp_f7.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "cmsis_fft_dsp_f7.hex"
	@echo 'Finished building: $@'
	@echo ' '

cmsis_fft_dsp_f7.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "cmsis_fft_dsp_f7.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	arm-none-eabi-objcopy.exe -O ihex "cmsis_fft_dsp_f7.elf" "cmsis_fft_dsp_f7.hex"
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY: post-build

-include ../makefile.targets
