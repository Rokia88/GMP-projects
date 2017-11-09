################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cast.c \
../echange_1.c \
../echange_2.c \
../endianness.c \
../incrementation_1.c \
../incrementation_2.c \
../pointeur_1.c \
../pointeur_2-3.c 

OBJS += \
./cast.o \
./echange_1.o \
./echange_2.o \
./endianness.o \
./incrementation_1.o \
./incrementation_2.o \
./pointeur_1.o \
./pointeur_2-3.o 

C_DEPS += \
./cast.d \
./echange_1.d \
./echange_2.d \
./endianness.d \
./incrementation_1.d \
./incrementation_2.d \
./pointeur_1.d \
./pointeur_2-3.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


