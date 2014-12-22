################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../links/Ds1621.cpp 

OBJS += \
./links/Ds1621.o 

CPP_DEPS += \
./links/Ds1621.d 


# Each subdirectory must supply rules for building sources it contributes
links/%.o: ../links/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/home/micha/workspace/DS1621_utest/links" -I"/home/micha/workspace/wiringPi_gmock/mocks" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


