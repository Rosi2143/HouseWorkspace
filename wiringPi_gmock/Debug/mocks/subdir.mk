################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../mocks/wiringPiI2C_Mock.cpp \
../mocks/wiringPi_Mock.cpp 

OBJS += \
./mocks/wiringPiI2C_Mock.o \
./mocks/wiringPi_Mock.o 

CPP_DEPS += \
./mocks/wiringPiI2C_Mock.d \
./mocks/wiringPi_Mock.d 


# Each subdirectory must supply rules for building sources it contributes
mocks/%.o: ../mocks/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


