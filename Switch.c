/*
 * Switch.c
 *
 *  Created on: January 12, 2026
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
    IOMUX->SECCFG.PINCM[PB12INDEX] = 0x00040081; //set as input
    IOMUX->SECCFG.PINCM[PB17INDEX] = 0x00040081;
   
 
}
// return current state of switches
uint32_t Switch_In(void){
    // write this
  return ((GPIOB->DIN31_0 >> 12) | (GPIOB->DIN31_0 >> 16) )& 0x03; 

  
}
