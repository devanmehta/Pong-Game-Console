// Lab9Main.c
// Runs on MSPM0G3507
// Pong - Lab 9 ECE319K
// Students: Tanish Muralidhar & Devan Mehta
// Last Modified: April 16, 2026
//
// Landscape LCD: 160px wide x 128px tall
// Player 1 (Right Paddle): PB24, ADC1 channel 6  -> ADC1_Init(6,0) / ADC1_In()
// Player 2 (Left  Paddle): PB18, ADC0 channel 5  -> ADC0_Init(5,0) / ADC0_In()
//


#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
#include "../inc/ADC.h"      // header only - ADC.c - NO MORE ADC1
#include "../inc/DAC5.h"
#include "../inc/Arabic.h"
#include "SmallFont.h"
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h"

// ========== Global Game Variables ==========
uint32_t rightPaddleY = 40;  // Player 1 right paddle top-edge Y (PB24)
uint32_t leftPaddleY  = 40;  // Player 2 left  paddle top-edge Y (PB18)
// uint32_t semaphore    = 0;   // set by ISR, cleared by main5 OLD

// ========== Clock ==========
void PLL_Init(void){
  Clock_Init80MHz(0);
}

// // ========== OLD Convert ==========
// // Landscape LCD: 160px wide x 128px tall
// // Score bar: y=0 to y=9 (10px reserved)
// // Play area: y=10 to y=127
// // Paddle height = 30px
// // Max top edge  = 127 - 30 = 97
// // Usable range  = 97 - 10  = 87
// // Maps 0-4095 -> 0-87, caller adds +10 for score bar offset
// uint32_t Convert(uint32_t input){
//   return ((input * 1617)>>12) + 214;
// }

// ========== Random ==========
uint32_t M = 1;
uint32_t Random32(void){ M = 1664525*M+1013904223; return M; }
uint32_t Random(uint32_t n){ return (Random32()>>16)%n; }

// ========== TExaS Logic Analyzer ==========
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

// // ========== OLD STARTER CODE 30 Hz Game Engine ISR ==========
// void TIMG12_IRQHandler(void){
//   if((TIMG12->CPU_INT.IIDX) == 1){
//     GPIOB->DOUTTGL31_0 = GREEN;
//     GPIOB->DOUTTGL31_0 = GREEN;

//     // 1) Sample both slide pots independently
//     rightPaddleY = 10 + Convert(ADC1_In()); // ADC1 ch6 PB24 - Player 1 right
//     leftPaddleY  = 10 + Convert(ADC0_In()); // ADC0 ch5 PB18 - Player 2 left

//     // 2) Read input switches
//     // 3) Move sprites / ball physics
//     // 4) Start sounds
//     // 5) Set semaphore
//     semaphore = 1;

//     GPIOB->DOUTTGL31_0 = GREEN;
//   }
// }

// ========== Language Support ==========
typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage = English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[]       = "Hello";
const char Hello_Spanish[]       = "\xADHola!";
const char Hello_Portuguese[]    = "Ol\xA0";
const char Hello_French[]        = "All\x83";
const char Goodbye_English[]     = "Goodbye";
const char Goodbye_Spanish[]     = "Adi\xA2s";
const char Goodbye_Portuguese[]  = "Tchau";
const char Goodbye_French[]      = "Au revoir";
const char Language_English[]    = "English";
const char Language_Spanish[]    = "Espa\xA4ol";
const char Language_Portuguese[] = "Portugu\x88s";
const char Language_French[]     = "Fran\x87" "ais";
const char *Phrases[3][4]={
  {Hello_English,    Hello_Spanish,    Hello_Portuguese,    Hello_French},
  {Goodbye_English,  Goodbye_Spanish,  Goodbye_Portuguese,  Goodbye_French},
  {Language_English, Language_Spanish, Language_Portuguese, Language_French}
};

// ========== Arabic Demo ==========
Arabic_t ArabicAlphabet[]={
  alif,ayh,baa,daad,daal,dhaa,dhaal,faa,ghayh,haa,ha,
  jeem,kaaf,khaa,laam,meem,noon,qaaf,raa,saad,seen,sheen,
  ta,thaa,twe,waaw,yaa,zaa,space,dot,null
};
Arabic_t Hello_Ar[]   = {alif,baa,ha,raa,meem,null};
Arabic_t Honored_Ar[] = {alif,noon,waaw,ta,faa,raa,sheen,null};

// ========== main0: Arabic Test ==========
int main0(void){
  Clock_Init80MHz(0);
  LaunchPad_Init();
  ST7735_InitR(INITR_REDTAB);
  ST7735_FillScreen(ST7735_WHITE);
  Arabic_SetCursor(0,15); Arabic_OutString(Hello_Ar);
  Arabic_SetCursor(0,31); Arabic_OutString(Honored_Ar);
  Arabic_SetCursor(0,63); Arabic_OutString(ArabicAlphabet);
  while(1){}
}

// ========== main1: Language Test ==========
int main1(void){
  char l;
  __disable_irq();
  PLL_Init();
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB);
  ST7735_FillScreen(0x0000);
  for(phrase_t myPhrase=HELLO; myPhrase<=GOODBYE; myPhrase++){
    for(Language_t myL=English; myL<=French; myL++){
      ST7735_OutString((char*)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
      ST7735_OutString((char*)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j<3; j++){
      for(int i=0; i<16; i++){
        ST7735_SetCursor(7*j+0,i); ST7735_OutUDec(l);
        ST7735_OutChar(' '); ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i); ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// ========== main2: Sprite Test ==========
int main2(void){
  __disable_irq();
  PLL_Init();
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB);
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_DrawBitmap(22,  159, PlayerShip0,       18, 8);
  ST7735_DrawBitmap(53,  151, Bunker0,            18, 5);
  ST7735_DrawBitmap(42,  159, PlayerShip1,        18, 8);
  ST7735_DrawBitmap(62,  159, PlayerShip2,        18, 8);
  ST7735_DrawBitmap(82,  159, PlayerShip3,        18, 8);
  ST7735_DrawBitmap(0,     9, SmallEnemy10pointA, 16,10);
  ST7735_DrawBitmap(20,    9, SmallEnemy10pointB, 16,10);
  ST7735_DrawBitmap(40,    9, SmallEnemy20pointA, 16,10);
  ST7735_DrawBitmap(60,    9, SmallEnemy20pointB, 16,10);
  ST7735_DrawBitmap(80,    9, SmallEnemy30pointA, 16,10);
  for(uint32_t t=500; t>0; t=t-5){
    SmallFont_OutVertical(t,104,6);
    Clock_Delay1ms(50);
  }
  ST7735_FillScreen(0x0000);
  ST7735_SetCursor(1,1); ST7735_OutString("GAME OVER");
  ST7735_SetCursor(1,2); ST7735_OutString("Nice try,");
  ST7735_SetCursor(1,3); ST7735_OutString("Earthling!");
  ST7735_SetCursor(2,4); ST7735_OutUDec(1234);
  while(1){}
}

// ========== main3: Switch + LED Test ==========
int main3(void){
  __disable_irq();
  PLL_Init();
  LaunchPad_Init();
  Switch_Init();
  LED_Init();
  while(1){
    // write code to test switches and LEDs
  }
}

// ========== main4: Sound Test ==========
int main4(void){ uint32_t last=0, now;
  __disable_irq();
  PLL_Init();
  LaunchPad_Init();
  Switch_Init();
  LED_Init();
  Sound_Init();
  TExaS_Init(ADC0, 6, 0);
  __enable_irq();
  while(1){
    now = Switch_In();
    if((last==0)&&(now==1)) Sound_Shoot();
    if((last==0)&&(now==2)) Sound_Killed();
    if((last==0)&&(now==4)) Sound_Explosion();
    if((last==0)&&(now==8)) Sound_Fastinvader1();
    last = now;
  }
}

// ========== main: Slide Pot Test ==========
// Verifies both slide pots work independently
// P1 bar = CYAN  (right side of screen)
// P2 bar = MAGENTA (left side of screen)
// Switch to main5() when ready for full game
int mainT(void){
  __disable_irq();
  Clock_Init80MHz(0);
  LaunchPad_Init();
  ST7735_InitPrintf(INITR_REDTAB);
  ST7735_FillScreen(ST7735_BLACK);

  ADC1_Init(6, 0);  // Player 1 right paddle - PB24 ADC1 ch6
  ADC0_Init(5, 0);  // Player 2 left  paddle - PB18 ADC0 ch5

  ST7735_SetCursor(0,0); ST7735_OutString("SLIDEPOT TEST");
  ST7735_SetCursor(0,2); ST7735_OutString("P1 ADC1 PB24:");
  ST7735_SetCursor(0,4); ST7735_OutString("P2 ADC0 PB18:");

  __enable_irq();

  uint32_t p1Raw, p2Raw;
  while(1){
    p1Raw = ADC1_In();  // PB24 Player 1
    p2Raw = ADC0_In();  // PB18 Player 2

    ST7735_SetCursor(0,3); ST7735_OutUDec(p1Raw); ST7735_OutString("    ");
    ST7735_SetCursor(0,5); ST7735_OutUDec(p2Raw); ST7735_OutString("    ");

    Clock_Delay1ms(100);
  }
}



//OUR PONG SPRITE TEST
int main6(void){
  __disable_irq();
  PLL_Init();
  LaunchPad_Init();
  ST7735_InitR(INITR_REDTAB);
  ST7735_SetRotation(1);         // landscape: 160 wide x 128 tall
  ST7735_FillScreen(ST7735_BLACK);

  // Score bar divider
  ST7735_DrawFastHLine(0, 8, 160, ST7735_WHITE);

  // Score text
  ST7735_SetCursor(0, 0); ST7735_OutString("P1:0");
  ST7735_SetCursor(9, 0); ST7735_OutString("P2:0");

  // Left paddle at x=2, centered vertically in play area
  // Play area height = 127-9 = 118, paddle=30, center top = 9+(118-30)/2 = 53
  // y_bottom = 53 + 30 - 1 = 82
  ST7735_DrawBitmap(2,   82, playerrect1, 5, 30);

  // Right paddle at x=148 (160 - 5 - 7 margin), same y
  ST7735_DrawBitmap(148, 82, playerrect2, 5, 30);

  // Ball centered: x=(160-10)/2=75, top=9+(118-10)/2=63 -> y_bottom=72
  ST7735_DrawBitmap(75,  72, ball, 10, 10);

  while(1){}
}

//our button to screen test
int mainB(void){
  __disable_irq();
  PLL_Init();
  LaunchPad_Init();
  Switch_Init();
  LED_Init();
  ST7735_InitR(INITR_REDTAB);
  ST7735_SetRotation(1); // landscape 160x128
  ST7735_FillScreen(ST7735_BLACK);

  ST7735_SetCursor(0, 0); ST7735_OutString("SWITCH TEST");
  ST7735_SetCursor(0, 2); ST7735_OutString("TOP  PB12 count:");
  ST7735_SetCursor(0, 4); ST7735_OutString("BOT  PB17 count:");

  __enable_irq();

  uint32_t count1 = 0;
  uint32_t count2 = 0;
  uint32_t last1  = 0;
  uint32_t last2  = 0;
  uint32_t sw, now1, now2;

  while(1){
    sw   = Switch_In();
    now1 = sw & 0x01; // bit0 = PB12 top
    now2 = sw & 0x02; // bit1 = PB17 bottom

    if((last1 == 0) && (now1 != 0)) count1++;// rising edge
    if((last2 == 0) && (now2 != 0)) count2++;// rising edge

    last1 = now1;
    last2 = now2;

    ST7735_SetCursor(0, 3); ST7735_OutUDec(count1); ST7735_OutString("    ");
    ST7735_SetCursor(0, 5); ST7735_OutUDec(count2); ST7735_OutString("    ");

    Clock_Delay1ms(10);// debounce delay
  }
}





//-------------------------------------------------------------

// FULL PONG GAME starts here
uint32_t semaphore = 0;  
uint32_t last_sw = 0;
// States: 0 = PAUSED, 1 = PLAYING, 2 = START SCREEN, 3 = GAME OVER
uint32_t game_state = 2; 

// Language: 0 = English, 1 = Spanish
uint32_t pongLanguage = 0; 
const char *Pong_Lang_Name[2]     = {"English", "Espanol"};
const char *Pong_P1_Score_Text[2] = {"P1:", "J1:"};
const char *Pong_P2_Score_Text[2] = {"P2:", "J2:"};
const char *Pong_Win_Text[2]      = {" WINS! ", " GANA! "};

// Scores
uint32_t score1 = 0; // Left Player
uint32_t score2 = 0; // Right Player

// Paddle Positions (Y coordinates of the top edge)
int32_t paddleL_Y = 53, old_paddleL_Y = 53;
int32_t paddleR_Y = 53, old_paddleR_Y = 53;

// Ball Positions and Velocity
int32_t ball_X = 75, old_ball_X = 75;
int32_t ball_Y = 63, old_ball_Y = 63;
int32_t ball_VX = -2; // Starts moving left
int32_t ball_VY = 2;  // Starts moving down


// HELPER FUNCTIONS
// Maps ADC (0-4095) to usable Y screen space (10 to 97)
int32_t Pong_Convert(uint32_t input){
  return ((input * 87) >> 12) + 10; 
}

// Resets ball to center
void Pong_Reset_Ball(void){
  ball_X = 75;
  ball_Y = 63;
  ball_VY = 2;
}


// 30 HZ GAME ENGINE - TIMG12_IRQHandler
void TIMG12_IRQHandler(void){
  if((TIMG12->CPU_INT.IIDX) == 1){
    
    uint32_t now_sw = Switch_In();
    
    // STATE 2: START SCREEN & STATE 3: GAME OVER
    if(game_state == 2 || game_state == 3){
        if((last_sw == 0) && (now_sw == 2)){ // PB17 (Bottom) - Toggle Language
            pongLanguage = (pongLanguage + 1) % 2;
        }
        if((last_sw == 0) && (now_sw == 1)){ // PB12 (Top) - Start Game
            score1 = 0;
            score2 = 0;
            Pong_Reset_Ball();
            game_state = 1; 
            ST7735_FillScreen(ST7735_BLACK); 
            ST7735_DrawFastHLine(0, 9, 160, ST7735_WHITE); 
        }
    }
    // STATE 0 & 1: PLAYING OR PAUSED
    else {
        if((last_sw == 0) && (now_sw == 1)){ game_state = 1; } // Play
        if((last_sw == 0) && (now_sw == 2)){ game_state = 0; } // Pause
    }

    last_sw = now_sw;

    // GAME PHYSICS (active if playing)
    if(game_state == 1){
        paddleL_Y = Pong_Convert(ADC1_In()); 
        paddleR_Y = Pong_Convert(ADC0_In()); 
        
        ball_X += ball_VX;
        ball_Y += ball_VY;

        // Top/Bottom Walls
        if(ball_Y <= 10){ 
            ball_Y = 10; ball_VY = -ball_VY; Sound_Hit(); 
        }
        if(ball_Y >= 117){ 
            ball_Y = 117; ball_VY = -ball_VY; Sound_Hit();
        }

        // Left Paddle
        if(ball_X <= 7 && ball_X >= 2){
            if((ball_Y + 10 >= paddleL_Y) && (ball_Y <= paddleL_Y + 30)){
                ball_X = 8; ball_VX = -ball_VX; Sound_Paddle();
            }
        }

        // Right Paddle
        if(ball_X + 10 >= 148 && ball_X <= 153){
            if((ball_Y + 10 >= paddleR_Y) && (ball_Y <= paddleR_Y + 30)){
                ball_X = 137; ball_VX = -ball_VX; Sound_Paddle();
            }
        }

        // Scoring
        if(ball_X < 0){ 
            score2++; Sound_Win(); Pong_Reset_Ball(); 
        }
        if(ball_X > 150){ 
            score1++; Sound_Win(); Pong_Reset_Ball(); 
        }

        // Win Condition
        if(score1 == 3 || score2 == 3){
            game_state = 3; 
            ST7735_FillScreen(ST7735_BLACK);
        }
    }

    semaphore = 1; 
  }
}


// MAIN LOOP (foreground, our main 5)
int main(void){
  __disable_irq();
  Clock_Init80MHz(0);
  LaunchPad_Init();
  
  ST7735_InitR(INITR_REDTAB);
  ST7735_SetRotation(1); 
  ST7735_FillScreen(ST7735_BLACK);

  ADC1_Init(6, 0);  
  ADC0_Init(5, 0);  
  Switch_Init();
  Sound_Init();
  
  TimerG12_IntArm(80000000/30, 2); 
  __enable_irq();

  while(1){
    while(!semaphore){}  
    semaphore = 0;       

    // RENDER: START SCREEN
    if(game_state == 2){
        ST7735_SetCursor(5, 2); ST7735_OutString("P O N G");
        ST7735_SetCursor(1, 6); ST7735_OutString("PB17 Toggle Lang:");
        ST7735_SetCursor(5, 8); ST7735_OutString((char *)Pong_Lang_Name[pongLanguage]);
        ST7735_OutString("   "); 
        ST7735_SetCursor(1, 12); ST7735_OutString("PB12 To Start Game");
    }

    // RENDER: PLAYING
    else if(game_state == 1){
        ST7735_SetCursor(6, 6); ST7735_OutString("      ");

        if(old_ball_X != ball_X || old_ball_Y != ball_Y){
            ST7735_FillRect(old_ball_X, old_ball_Y, 10, 10, ST7735_BLACK);
        }
        if(old_paddleL_Y != paddleL_Y){
            ST7735_FillRect(2, old_paddleL_Y, 5, 30, ST7735_BLACK);
        }
        if(old_paddleR_Y != paddleR_Y){
            ST7735_FillRect(148, old_paddleR_Y, 5, 30, ST7735_BLACK);
        }

        ST7735_DrawBitmap(2, paddleL_Y + 29, playerrect1, 5, 30);
        ST7735_DrawBitmap(148, paddleR_Y + 29, playerrect2, 5, 30);
        ST7735_DrawBitmap(ball_X, ball_Y + 9, ball, 10, 10);

        old_ball_X = ball_X;
        old_ball_Y = ball_Y;
        old_paddleL_Y = paddleL_Y;
        old_paddleR_Y = paddleR_Y;

        ST7735_SetCursor(0, 0); 
        ST7735_OutString((char *)Pong_P1_Score_Text[pongLanguage]);
        ST7735_OutUDec(score1);

        ST7735_SetCursor(9, 0); 
        ST7735_OutString((char *)Pong_P2_Score_Text[pongLanguage]);
        ST7735_OutUDec(score2);
    }

    // RENDER: PAUSED
    else if(game_state == 0){
        ST7735_SetCursor(6, 6);
        ST7735_OutString("PAUSED");
    }

    // RENDER: GAME OVER
    else if(game_state == 3){
        ST7735_SetCursor(4, 4);
        if(score1 == 3){
            ST7735_OutString((char *)Pong_P1_Score_Text[pongLanguage]);
        } else {
            ST7735_OutString((char *)Pong_P2_Score_Text[pongLanguage]);
        }
        ST7735_OutString((char *)Pong_Win_Text[pongLanguage]);
        
        ST7735_SetCursor(1, 10);
        ST7735_OutString("PB12 To Play Again");
    }
  }
}