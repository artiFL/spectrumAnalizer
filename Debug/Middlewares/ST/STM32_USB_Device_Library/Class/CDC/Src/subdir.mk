################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c 

OBJS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.o: ../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -D__FPU_PRESENT '-D__packed=__attribute__((__packed__))' '-D__weak=__attribute__((weak))' -DARM_MATH_CM7 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Lib" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Lib/GCC" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Lib/ARM" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/DSP" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Drivers/CMSIS/GCC" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Drivers/CMSIS/ARM" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Drivers/CMSIS/IAR" -I../USB_DEVICE/App -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/USB_DEVICE/App" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/USB_DEVICE/Target" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Middlewares/ST/STM32_USB_Device_Library/Core/Src" -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Core/core/inc" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Core/core/src" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Core/display" -I"C:/Users/flegler.a/Desktop/Work_space/git_clone/spectrumAnalizer/Core/display/Font" -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -Wfatal-errors -fstack-usage -MMD -MP -MF"Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

