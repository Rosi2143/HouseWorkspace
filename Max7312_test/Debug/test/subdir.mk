################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/main.cpp 

OBJS += \
./test/main.o 

CPP_DEPS += \
./test/main.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/micha/workspace/Max7312_test/links" -I"/home/micha/workspace/wiringPi_gmock/mocks" -I"/home/micha/workspace/Max7312/Interfaces" -O0 -g3 -Wall -c -fmessage-length=0 -Wconversion-null -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


