################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BlindStates.cpp \
../src/BlindSwitchIn.cpp \
../src/Floor.cpp \
../src/HeaterSwitchIn.cpp \
../src/House.cpp \
../src/LightSwitchIn.cpp \
../src/Room.cpp \
../src/SwitchIn.cpp 

OBJS += \
./src/BlindStates.o \
./src/BlindSwitchIn.o \
./src/Floor.o \
./src/HeaterSwitchIn.o \
./src/House.o \
./src/LightSwitchIn.o \
./src/Room.o \
./src/SwitchIn.o 

CPP_DEPS += \
./src/BlindStates.d \
./src/BlindSwitchIn.d \
./src/Floor.d \
./src/HeaterSwitchIn.d \
./src/House.d \
./src/LightSwitchIn.d \
./src/Room.d \
./src/SwitchIn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


