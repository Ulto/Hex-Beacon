################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APA102.c \
../Src/dma.c \
../Src/gpio.c \
../Src/main.c \
../Src/spi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/APA102.o \
./Src/dma.o \
./Src/gpio.o \
./Src/main.o \
./Src/spi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/APA102.d \
./Src/dma.d \
./Src/gpio.d \
./Src/main.d \
./Src/spi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F401xE -I"/home/zach/STM32/workspace/HexBeacon_rev0.2/Inc" -I"/home/zach/STM32/workspace/HexBeacon_rev0.2/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/zach/STM32/workspace/HexBeacon_rev0.2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/zach/STM32/workspace/HexBeacon_rev0.2/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/zach/STM32/workspace/HexBeacon_rev0.2/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


