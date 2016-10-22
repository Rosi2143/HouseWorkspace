################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../blink.cpp 

OBJS += \
./blink.o 

CPP_DEPS += \
./blink.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -I"/home/micha/rpi/projects/HouseWorkspace/../HSHSB3_C/WiringPi/wiringPi" -I"/home/micha/rpi/projects/HouseWorkspace/../HSHSB3_C/WiringPi/devLib" -I/mnt/piusrinclude -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


