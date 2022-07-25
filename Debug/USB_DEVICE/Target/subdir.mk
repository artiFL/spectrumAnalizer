################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_DEVICE/Target/usbd_conf.c 

OBJS += \
./USB_DEVICE/Target/usbd_conf.o 

C_DEPS += \
./USB_DEVICE/Target/usbd_conf.d 


# Each subdirectory must supply rules for building sources it contributes
USB_DEVICE/Target/%.o: ../USB_DEVICE/Target/%.c USB_DEVICE/Target/subdir.mk
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -D__FPU_PRESENT '-D__packed=__attribute__((__packed__))' '-D__weak=__attribute__((weak))' -DARM_MATH_CM7 -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Lib" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Lib/GCC" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Lib/ARM" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/DSP" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Drivers/CMSIS/GCC" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Drivers/CMSIS/ARM" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Drivers/CMSIS/IAR" -I../USB_DEVICE/App -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/USB_DEVICE/App" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/USB_DEVICE/Target" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Middlewares/ST/STM32_USB_Device_Library/Core/Src" -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Core/core/inc" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Core/core/src" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Core/display" -I"/Users/artemflegler/Desktop/Atolic_truestudio/cmsis_fft_dsp_f7/Core/display/Font" -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -Wfatal-errors -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-USB_DEVICE-2f-Target

clean-USB_DEVICE-2f-Target:
	-$(RM) ./USB_DEVICE/Target/usbd_conf.d ./USB_DEVICE/Target/usbd_conf.o

.PHONY: clean-USB_DEVICE-2f-Target

