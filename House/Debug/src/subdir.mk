################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Floor.cpp \
../src/House.cpp \
../src/Light.cpp \
../src/Room.cpp \
../src/Switch.cpp 

OBJS += \
./src/Floor.o \
./src/House.o \
./src/Light.o \
./src/Room.o \
./src/Switch.o 

CPP_DEPS += \
./src/Floor.d \
./src/House.d \
./src/Light.d \
./src/Room.d \
./src/Switch.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


