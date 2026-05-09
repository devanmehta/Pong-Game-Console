// Sound.c
// Runs on MSPM0
// Sound assets in sounds/sounds.h
// your name
// your data
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "sounds/sounds.h"
#include "../inc/DAC5.h"
#include "../inc/Timer.h"

const uint8_t *Sound_Pt; // Pointer to the current array of sound data
uint32_t Sound_Count = 0; // Number of samples left to play


void SysTick_IntArm(uint32_t period, uint32_t priority){
  SysTick->CTRL = 0x00;  	// disable SysTick during setup
  SysTick->LOAD = period-1;  // reload value
  SCB->SHP[1] = (SCB->SHP[1]&(~0xC0000000))|(priority<<30); // priority 2
  SysTick->VAL = 0;      	// any write to VAL clears COUNT and sets VAL equal to LOAD
  SysTick->CTRL = 0x07;      // enable SysTick with 80 MHz bus clock and interrupts


}
// initialize a 11kHz SysTick, however no sound should be started
// initialize any global variables
// Initialize the 5-bit DAC



void Sound_Init(void){
  DAC5_Init();              // 1. Initialize the 5-bit DAC pins (PB0-PB4)
    
    // 2. Use your helper function! 
    // 7272 is the period for 11kHz (80MHz / 11000). 
    // 0 is the highest priority.
    SysTick_IntArm(7272, 0);
 }




 
void SysTick_Handler(void){ // called at 11 kHz
 if(Sound_Count > 0){
        DAC5_Out(*Sound_Pt); // Output the current sample to the DAC
        Sound_Pt++;          // Move pointer to the next sample
        Sound_Count--;       // Decrement the samples remaining
    }

}


//******* Sound_Start ************
// This function does not output to the DAC.
// Rather, it sets a pointer and counter, and then enables the SysTick interrupt.
// It starts the sound, and the SysTick ISR does the output
// feel free to change the parameters
// Sound should play once and stop
// Input: pt is a pointer to an array of DAC outputs
//        count is the length of the array
// Output: none
// special cases: as you wish to implement
void Sound_Start(const uint8_t *pt, uint32_t count){
    __disable_irq();      // Pause interrupts to prevent race conditions
    Sound_Pt = pt;        // Set the pointer to the new sound array
    Sound_Count = count;  // Set the number of samples to play
    __enable_irq();       // Resume interrupts
 }


 
void Sound_Shoot(void){
    Sound_Start(shoot, 4080);
}

void Sound_Killed(void){
    Sound_Start(invaderkilled, 3377);
}

void Sound_Explosion(void){
    Sound_Start(explosion, 2000);
}

void Sound_Fastinvader1(void){
    Sound_Start(fastinvader1, 982);
}

void Sound_Fastinvader2(void){
    Sound_Start(fastinvader2, 1042);
}

void Sound_Fastinvader3(void){
    Sound_Start(fastinvader3, 1054);
}

void Sound_Fastinvader4(void){
    Sound_Start(fastinvader4, 1098);
}

void Sound_Highpitch(void){
    Sound_Start(highpitch, 1802);
}

void Sound_Hit(void){
    Sound_Start(hitSound, 1740);
}

void Sound_Paddle(void){
    Sound_Start(paddleSound, 3756);
}

void Sound_Win(void){
    Sound_Start(win, 22464);
}