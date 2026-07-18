################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../inc/Clock.cpp \
../inc/DAC.cpp \
../inc/DAC5.cpp \
../inc/FIFO2.cpp \
../inc/LaunchPad.cpp \
../inc/SPI.cpp \
../inc/ST7735.cpp \
../inc/SlidePot.cpp \
../inc/TExaS.cpp \
../inc/Timer.cpp 

S_SRCS += \
../inc/SysTick.s \
../inc/msp.s 

C_SRCS += \
../inc/ADC.c \
../inc/ADC1.c \
../inc/Arabic.c \
../inc/Bump.c \
../inc/Clock.c \
../inc/DAC.c \
../inc/DAC5.c \
../inc/Dump.c \
../inc/EdgeTriggered.c \
../inc/FIFO.c \
../inc/FIFO1.c \
../inc/I2C.c \
../inc/InputCapture.c \
../inc/JoyStick.c \
../inc/Key.c \
../inc/LCD.c \
../inc/LaunchPad.c \
../inc/Motor.c \
../inc/PWM.c \
../inc/PWM1.c \
../inc/SPI.c \
../inc/SSD1306.c \
../inc/ST7735.c \
../inc/TExaS.c \
../inc/Timer.c \
../inc/UART.c \
../inc/UARTbusywait.c \
../inc/UARTints.c \
../inc/startup_mspm0g3507_ticlang.c 

S_DEPS += \
./inc/SysTick.d \
./inc/msp.d 

C_DEPS += \
./inc/ADC.d \
./inc/ADC1.d \
./inc/Arabic.d \
./inc/Bump.d \
./inc/Clock.d \
./inc/DAC.d \
./inc/DAC5.d \
./inc/Dump.d \
./inc/EdgeTriggered.d \
./inc/FIFO.d \
./inc/FIFO1.d \
./inc/I2C.d \
./inc/InputCapture.d \
./inc/JoyStick.d \
./inc/Key.d \
./inc/LCD.d \
./inc/LaunchPad.d \
./inc/Motor.d \
./inc/PWM.d \
./inc/PWM1.d \
./inc/SPI.d \
./inc/SSD1306.d \
./inc/ST7735.d \
./inc/TExaS.d \
./inc/Timer.d \
./inc/UART.d \
./inc/UARTbusywait.d \
./inc/UARTints.d \
./inc/startup_mspm0g3507_ticlang.d 

OBJS += \
./inc/ADC.o \
./inc/ADC1.o \
./inc/Arabic.o \
./inc/Bump.o \
./inc/Clock.o \
./inc/DAC.o \
./inc/DAC5.o \
./inc/Dump.o \
./inc/EdgeTriggered.o \
./inc/FIFO.o \
./inc/FIFO1.o \
./inc/FIFO2.o \
./inc/I2C.o \
./inc/InputCapture.o \
./inc/JoyStick.o \
./inc/Key.o \
./inc/LCD.o \
./inc/LaunchPad.o \
./inc/Motor.o \
./inc/PWM.o \
./inc/PWM1.o \
./inc/SPI.o \
./inc/SSD1306.o \
./inc/ST7735.o \
./inc/SlidePot.o \
./inc/SysTick.o \
./inc/TExaS.o \
./inc/Timer.o \
./inc/UART.o \
./inc/UARTbusywait.o \
./inc/UARTints.o \
./inc/msp.o \
./inc/startup_mspm0g3507_ticlang.o 

CPP_DEPS += \
./inc/Clock.d \
./inc/DAC.d \
./inc/DAC5.d \
./inc/FIFO2.d \
./inc/LaunchPad.d \
./inc/SPI.d \
./inc/ST7735.d \
./inc/SlidePot.d \
./inc/TExaS.d \
./inc/Timer.d 

OBJS__QUOTED += \
"inc\ADC.o" \
"inc\ADC1.o" \
"inc\Arabic.o" \
"inc\Bump.o" \
"inc\Clock.o" \
"inc\DAC.o" \
"inc\DAC5.o" \
"inc\Dump.o" \
"inc\EdgeTriggered.o" \
"inc\FIFO.o" \
"inc\FIFO1.o" \
"inc\FIFO2.o" \
"inc\I2C.o" \
"inc\InputCapture.o" \
"inc\JoyStick.o" \
"inc\Key.o" \
"inc\LCD.o" \
"inc\LaunchPad.o" \
"inc\Motor.o" \
"inc\PWM.o" \
"inc\PWM1.o" \
"inc\SPI.o" \
"inc\SSD1306.o" \
"inc\ST7735.o" \
"inc\SlidePot.o" \
"inc\SysTick.o" \
"inc\TExaS.o" \
"inc\Timer.o" \
"inc\UART.o" \
"inc\UARTbusywait.o" \
"inc\UARTints.o" \
"inc\msp.o" \
"inc\startup_mspm0g3507_ticlang.o" 

C_DEPS__QUOTED += \
"inc\ADC.d" \
"inc\ADC1.d" \
"inc\Arabic.d" \
"inc\Bump.d" \
"inc\Clock.d" \
"inc\DAC.d" \
"inc\DAC5.d" \
"inc\Dump.d" \
"inc\EdgeTriggered.d" \
"inc\FIFO.d" \
"inc\FIFO1.d" \
"inc\I2C.d" \
"inc\InputCapture.d" \
"inc\JoyStick.d" \
"inc\Key.d" \
"inc\LCD.d" \
"inc\LaunchPad.d" \
"inc\Motor.d" \
"inc\PWM.d" \
"inc\PWM1.d" \
"inc\SPI.d" \
"inc\SSD1306.d" \
"inc\ST7735.d" \
"inc\TExaS.d" \
"inc\Timer.d" \
"inc\UART.d" \
"inc\UARTbusywait.d" \
"inc\UARTints.d" \
"inc\startup_mspm0g3507_ticlang.d" 

CPP_DEPS__QUOTED += \
"inc\Clock.d" \
"inc\DAC.d" \
"inc\DAC5.d" \
"inc\FIFO2.d" \
"inc\LaunchPad.d" \
"inc\SPI.d" \
"inc\ST7735.d" \
"inc\SlidePot.d" \
"inc\TExaS.d" \
"inc\Timer.d" 

S_DEPS__QUOTED += \
"inc\SysTick.d" \
"inc\msp.d" 

C_SRCS__QUOTED += \
"../inc/ADC.c" \
"../inc/ADC1.c" \
"../inc/Arabic.c" \
"../inc/Bump.c" \
"../inc/Clock.c" \
"../inc/DAC.c" \
"../inc/DAC5.c" \
"../inc/Dump.c" \
"../inc/EdgeTriggered.c" \
"../inc/FIFO.c" \
"../inc/FIFO1.c" \
"../inc/I2C.c" \
"../inc/InputCapture.c" \
"../inc/JoyStick.c" \
"../inc/Key.c" \
"../inc/LCD.c" \
"../inc/LaunchPad.c" \
"../inc/Motor.c" \
"../inc/PWM.c" \
"../inc/PWM1.c" \
"../inc/SPI.c" \
"../inc/SSD1306.c" \
"../inc/ST7735.c" \
"../inc/TExaS.c" \
"../inc/Timer.c" \
"../inc/UART.c" \
"../inc/UARTbusywait.c" \
"../inc/UARTints.c" \
"../inc/startup_mspm0g3507_ticlang.c" 

CPP_SRCS__QUOTED += \
"../inc/Clock.cpp" \
"../inc/DAC.cpp" \
"../inc/DAC5.cpp" \
"../inc/FIFO2.cpp" \
"../inc/LaunchPad.cpp" \
"../inc/SPI.cpp" \
"../inc/ST7735.cpp" \
"../inc/SlidePot.cpp" \
"../inc/TExaS.cpp" \
"../inc/Timer.cpp" 

S_SRCS__QUOTED += \
"../inc/SysTick.s" \
"../inc/msp.s" 


