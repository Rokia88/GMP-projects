################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fact_native.c \
../parite.c \
../power_mod-2.c \
../power_mod_native.c 

OBJS += \
./fact_native.o \
./parite.o \
./power_mod-2.o \
./power_mod_native.o 

C_DEPS += \
./fact_native.d \
./parite.d \
./power_mod-2.d \
./power_mod_native.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


