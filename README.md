# Pong Game Console — TI MSPM0G3507

A two-player Pong game built from scratch running on Texas Instruments MSPM0G3507 microcontroller with LCD display and analog slide-pot controls. Features bilingual UI (English/Spanish) and sound effects — all running on bare-metal embedded C.

---

## Game Demo

https://youtu.be/v2CVBazpU2U?si=iJxxjaVZLvGU6vLO

---

## Features

- **Real-time Physics Engine**: 30 Hz ISR-driven game loop for accurate ball & paddle collision
- **Bilingual UI**: English/Spanish language toggle (button-selectable)
- **Smooth Analog Control**: ADC-based slide-pot paddle input for natural movement
- **Score Tracking**: First player to 3 points wins
- **Sound Effects**: Hit/paddle/win audio via DAC output
- **State Machine**: Clean game states (START → PLAYING → PAUSED → GAME OVER)
- **Full Game Pause**: Real-time pause/resume during gameplay

---

## Hardware

| Component | Pin / Channel | Purpose |
| :--- | :--- | :--- |
| **Microcontroller** | — | Main CPU (80 MHz) |
| **LCD Display** | SPI (PB6–PB9, PB15, PA13) | 160×128 pixel landscape display |
| **Player 1 Slide Pot** | PB24 / ADC1 Ch 6 | Right paddle Y-axis control |
| **Player 2 Slide Pot** | PB18 / ADC0 Ch 5 | Left paddle Y-axis control |
| **Top Push Button** | PB17 | Toggle Language / Pause Game |
| **Bottom Push Button** | PB12 | Start Game / Play Again / Resume |
| **Audio Speaker** | PB0–PB4 (5-bit Binary-Weighted DAC) | Sound effects generation |

---

## How to Play

### Gameplay

1. **START SCREEN**: Press PB17 to toggle English ↔ Spanish. Press PB12 to begin.
2. **PLAYING**: Move your paddle using slide pot. Ball bounces off paddles with sound effect and walls with sound effect
3. **PAUSED**: Press PB17 during gameplay to pause. Press PB12 to resume.
4. **SCORING**: Ball passes opponent's paddle = +1 point with sound effect.
5. **WIN**: First player to 3 points wins. Press PB12 to play again.

---

## Build & Flash

### Prerequisites
- **Code Composer Studio (CCS)** v12+
- **MSPM0 SDK** installed
- **LaunchPad connected** via USB

### Build Steps

1. **Open Code Composer Studio**
2. **File → Open Projects from File System**
   - Browse to `Pong-Game-Console` folder
   - Click **Finish**
3. **Project → Build** (or **Ctrl+B**)
   - Check **Console** tab for errors
4. **Run → Debug** (or **F11**)
   - CCS flashes and starts debugger
5. **Run → Resume** (or **F8**) to start
6. **Press a button** to interact with game!

### Common Build Errors & Fixes

| Error | Cause | Fix |
|-------|-------|-----|
| `Cannot find include file 'ti/devices/msp/...'` | Missing SDK path | Project → Properties → CCS Build → Include Options → verify MSPM0 SDK path |
| `Unresolved symbol '_c_int00'` | Missing startup file | Ensure `startup_MSPM0G3507_ccs.c` is in your project |
| `Port not found / Device not detected` | USB not connected | Check LaunchPad USB cable; try different port |
| `Build successful but no output` | Debugger issue | Try **Run → Terminate** then **Run → Debug** again |

---

## File Structure

Pong-Game-Console/
├── .gitignore                   
├── Lab9Main.c                   # Tester functions + Main pong game
├── mspm0g3507.cmd               # Linker command file for MSPM0G3507
│
├── Sound.c / Sound.h            # DAC sound generation & audio sample playback
├── Switch.c / Switch.h          # Debounced edge-triggered button drivers
├── SmallFont.c / SmallFont.h    # LCD bitmap typography and string rendering
│
├── images/                      # 16-bit color BMP sprite arrays (ball, paddles)
├── sounds/                      # Digital audio sample arrays
├── designdocuments/             # System diagrams and initial project proposals
│
└── inc/                         
    ├── ST7735.c / ST7735.h      # SPI LCD display driver
    ├── Clock.c / Clock.h        # 80 MHz PLL initialization
    ├── ADC.c / ADC.h            # Dual ADC sampling
    ├── Timer.c / Timer.h        # Periodic interrupt timer (TIMG12)
    └── DAC5.c / DAC5.h          # 5-bit resistor DAC 

---

## Code Architecture

### 30 Hz Game Physics ISR (TIMG12_IRQHandler)

Executes every 33.3 ms:
1. Poll Buttons (PB12 / PB17)
2. Sample ADCs & Convert to Y-Coordinates using fixed-point bit-shifting
3. Update Ball Position (X += VX, Y += VY)
4. Collision Detection & Audio Triggers
6. Check scoring (ball off-screen)
7. Set semaphore for main loop to render

### Main Loop (Foreground Rendering)

Wait for semaphore == 1, then clear it (semaphore = 0)
2. Switch game state:
 - State 2 (Start Screen): Render Text Menu & Language
 - State 1 (Playing): Clear Old Sprites -> Draw New Sprites -> Update Scores
 - State 0 (Paused): Render "PAUSED" Overlay
 - State 3 (Game Over): Render Winner Text & Listen for Reset

---

## Future Enhancements
- [ ] Power-ups (speed boost, paddle expansion)
- [ ] More game modes (survival, time attack)
- [ ] Building a housing and a transferring wiring to a PCB for a more polished finish