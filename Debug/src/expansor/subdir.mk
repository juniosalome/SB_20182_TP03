################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/expansor/expansor.c \
../src/expansor/lista.c \
../src/expansor/main.c 

OBJS += \
./src/expansor/expansor.o \
./src/expansor/lista.o \
./src/expansor/main.o 

C_DEPS += \
./src/expansor/expansor.d \
./src/expansor/lista.d \
./src/expansor/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/expansor/%.o: ../src/expansor/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


