################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ccd.c \
../ccdpp.c \
../cntrl.c \
../codec.c \
../main.c \
../uat.c 

OBJS += \
./ccd.o \
./ccdpp.o \
./cntrl.o \
./codec.o \
./main.o \
./uat.o 

C_DEPS += \
./ccd.d \
./ccdpp.d \
./cntrl.d \
./codec.d \
./main.d \
./uat.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


