################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Max7312.cpp 

OBJS += \
./src/Max7312.o 

CPP_DEPS += \
./src/Max7312.d 


# Each subdirectory must supply rules for building sources it contributes
src/Max7312.o: ../src/Max7312.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++1y -I/home/micha/mntpi/wiringPi/wiringPi/wiringPi -I/home/micha/git_repositories/wiringPi/wiringPi -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/Max7312.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


