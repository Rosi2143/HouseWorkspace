################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../links/Max7312.cpp 

OBJS += \
./links/Max7312.o 

CPP_DEPS += \
./links/Max7312.d 


# Each subdirectory must supply rules for building sources it contributes
links/%.o: ../links/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/micha/workspace/Max7312_test/links" -I"/home/micha/workspace/wiringPi_gmock/mocks" -I"/home/micha/workspace/Max7312/Interfaces" -O0 -g3 -Wall -c -fmessage-length=0 -Wconversion-null -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


