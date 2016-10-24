################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
/usr/src/gmock/gmock-all.cc 

CPP_SRCS += \
/home/micha/rpi/projects/HouseWorkspace/Ds1621/src/Ds1621.cpp 

CC_DEPS += \
./links/gmock-all.d 

OBJS += \
./links/Ds1621.o \
./links/gmock-all.o 

CPP_DEPS += \
./links/Ds1621.d 


# Each subdirectory must supply rules for building sources it contributes
links/Ds1621.o: /home/micha/rpi/projects/HouseWorkspace/Ds1621/src/Ds1621.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/home/micha/rpi/projects/HouseWorkspace/Ds1621/src" -I"/home/micha/rpi/projects/HouseWorkspace/wiringPi_gmock/mocks" -I"/home/micha/rpi/projects/HouseWorkspace/../HSHSB3_C/WiringPi/wiringPi/" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

links/gmock-all.o: /usr/src/gmock/gmock-all.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I"/home/micha/rpi/projects/HouseWorkspace/Ds1621/src" -I"/home/micha/rpi/projects/HouseWorkspace/wiringPi_gmock/mocks" -I"/home/micha/rpi/projects/HouseWorkspace/../HSHSB3_C/WiringPi/wiringPi/" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


