################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f767xx.s 

OBJS += \
./startup/startup_stm32f767xx.o 

S_DEPS += \
./startup/startup_stm32f767xx.d 


# Each subdirectory must supply rules for building sources it contributes
startup/startup_stm32f767xx.o: ../startup/startup_stm32f767xx.s startup/subdir.mk
	arm-none-eabi-gcc -c -mcpu=cortex-m7 -g3 -c -mfloat-abi=soft -Wa,-W -MMD -MP -MF"startup/startup_stm32f767xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

