################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/_org/main.c \
../src/_org/timer.c 

OBJS += \
./src/_org/main.o \
./src/_org/timer.o 

C_DEPS += \
./src/_org/main.d \
./src/_org/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/_org/%.o: ../src/_org/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"/home/micha/workspace/Timer/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


