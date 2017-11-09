################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fact_1.c \
../fact_2.c \
../fact_3.c \
../fact_3.timing.c \
../probable_prime.c 

OBJS += \
./fact_1.o \
./fact_2.o \
./fact_3.o \
./fact_3.timing.o \
./probable_prime.o 

C_DEPS += \
./fact_1.d \
./fact_2.d \
./fact_3.d \
./fact_3.timing.d \
./probable_prime.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


