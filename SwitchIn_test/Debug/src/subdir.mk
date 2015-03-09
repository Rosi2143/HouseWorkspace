################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SwitchIn.cpp \
../src/main.cpp 

OBJS += \
./src/SwitchIn.o \
./src/main.o 

CPP_DEPS += \
./src/SwitchIn.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/micha/workspace/Mocks/mocks" -I"/home/micha/workspace/House/interfaces" -I"/home/micha/workspace/SwitchIn_test/include" -I"/home/micha/workspace/TimeAndDate/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


