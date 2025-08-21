################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/apps/command_process/command_process.c 

OBJS += \
./Core/Src/apps/command_process/command_process.o 

C_DEPS += \
./Core/Src/apps/command_process/command_process.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/apps/command_process/%.o Core/Src/apps/command_process/%.su Core/Src/apps/command_process/%.cyclo: ../Core/Src/apps/command_process/%.c Core/Src/apps/command_process/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc/apps/system_config/framework -I../Core/Inc/apps/system_config -I../Core/Inc/apps/ -I../Core/Inc/apps/Control -I../Core/Inc/apps/command_process -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-apps-2f-command_process

clean-Core-2f-Src-2f-apps-2f-command_process:
	-$(RM) ./Core/Src/apps/command_process/command_process.cyclo ./Core/Src/apps/command_process/command_process.d ./Core/Src/apps/command_process/command_process.o ./Core/Src/apps/command_process/command_process.su

.PHONY: clean-Core-2f-Src-2f-apps-2f-command_process

