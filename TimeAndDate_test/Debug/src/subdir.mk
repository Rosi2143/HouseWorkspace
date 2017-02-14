################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
/usr/src/gmock/gmock-all.cc 

CPP_SRCS += \
../src/main.cpp 

CC_DEPS += \
./src/gmock-all.d 

OBJS += \
./src/gmock-all.o \
./src/main.o 

CPP_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/gmock-all.o: /usr/src/gmock/gmock-all.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/micha/rpi/projects/HouseWorkspace/House/interfaces" -I"/home/micha/rpi/projects/HouseWorkspace/TimeAndDate/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/micha/rpi/projects/HouseWorkspace/House/interfaces" -I"/home/micha/rpi/projects/HouseWorkspace/TimeAndDate/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


