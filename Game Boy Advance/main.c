#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"

//image library
#include "images/winbg.h"
#include "images/losebg.h"
#include "images/playercat.h"
#include "images/playercat2.h"
#include "images/wincat.h"
#include "images/losecat.h"
#include "images/catcat.h"
#include "images/bg.h"
#include "images/churu.h"
#include "images/gamecat.h"
#include "images/popcat.h"
#include "images/leftcat.h"
#include "images/rightcat.h"


enum gba_state {
  START,
  PLAY,
  WIN,
  LOSE,
  EXTRA
};

int isCollideWithLose(int playerX, int playerY) {
  if ((playerX + 5 >= 120 && playerX < 140 && playerY + 5 >= 70 && playerY < 90) ||
      (playerX + 5 >= 110 && playerX < 130 && playerY + 5 >= 90 && playerY < 110) ||
      (playerX + 5 >= 110 && playerX < 130 && playerY + 5 >= 10 && playerY < 30) ||
      (playerX + 5 >= 96 && playerX < 116 && playerY + 5 >= 30 && playerY < 50) ||
      (playerX + 5 >= 120 && playerX < 140 && playerY + 5 >= 220 && playerY < 240) ||
      (playerX + 5 >= 87 && playerX < 107 && playerY + 5 >= 220 && playerY < 240) ||
      (playerX + 5 >= 115 && playerX < 135 && playerY + 5 >= 200 && playerY < 220) ||
      (playerX + 5 >= 83 && playerX < 103 && playerY + 5 >= 180 && playerY < 200) ||
      (playerX + 5 >= 120 && playerX < 140 && playerY + 5 >= 30 && playerY < 50) ||
      (playerX + 5 >= 120 && playerX < 140 && playerY + 5 >= 50 && playerY < 70) ||
      (playerX + 5 >= 117 && playerX < 137 && playerY + 5 >= 160 && playerY < 180) ||
      (playerX + 5 >= 120 && playerX < 140 && playerY + 5 >= 150 && playerY < 170) ||
      (playerX + 5 >= 81 && playerX < 101 && playerY + 5 >= 130 && playerY < 150) ||
      (playerX + 5 >= 82 && playerX < 102 && playerY + 5 >= 152 && playerY < 172) ||
      (playerX + 5 >= 116 && playerX < 136 && playerY + 5 >= 120 && playerY < 140) ||
      (playerX + 5 >= 115 && playerX < 135 && playerY + 5 >= 110 && playerY < 130)) {
    return 1; // Collision 
  }

  return 0; // playercat is not collide with losecat
}


int isCollideWithWin(int playerX, int playerY) {
  if ((playerX + 10 >= 93 && playerX < 113 && playerY + 10 >= 97 && playerY < 117) ||
      (playerX + 10 >= 81 && playerX < 101 && playerY < 20) ||
      (playerX + 10 >= 114 && playerX < 134 && playerY + 10 >= 190 && playerY < 210)) {
    return 1; // Collision 
  }
  
  return 0; // playercat is not collide with wincat
}

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //

  REG_DISPCNT = MODE3 | BG2_ENABLE;
  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Counters to avoid tearing
  const struct info catplayer = {10, 10, 10};
  int catwidth = catplayer.catwidth;
  int catheight = catplayer.catheight;
  int anicounter = 1;
  int startcounter = 1;
  int playcounter = 1;
  int wincounter = 1;
  int losecounter = 1;
  int extracounter = 1;
  int defaultcat = 1;


  int playerX = 130;
  int playerY = 0;
  int life = 5;
  char lifeb[10];

  // Load initial application state
  enum gba_state state = START;

  while (1) {
    waitForVBlank();
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    switch (state) {
      case START:

        // for animation
        if (anicounter == 1) {
          drawImageDMA(43, 77, 80, 80, catcat);
          anicounter++;
        } else if (anicounter == 30) {
          drawImageDMA(43, 77, 80, 80, popcat);
          anicounter++;
        } else if (anicounter == 60) {
          drawImageDMA(43, 77, 80, 80, catcat);
          anicounter++;
        } else if (anicounter == 90) {
          drawImageDMA(43, 77, 80, 80, popcat);
          anicounter = -30;
        }
        anicounter++;
        
        // screen design
        if (startcounter) {
          drawFullScreenImageDMA(bg);
          drawString(23, 90, "MEOWTOPIA ", COLOR(30, 5, 21));
          drawImageDMA(43, 77, 80, 80, catcat);
          drawString(133, 59, "Press ENTER to Play!", COLOR(0, 0, 0));
          drawString(145, 27, "Press LEFT to choose your cat!", COLOR(0, 0, 0));
          startcounter = 0;
        }

        // press enter to start, press left arrow to extra
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          fillScreenDMA(BLACK);
          vBlankCounter = 0;
          life = 5;
          state = PLAY;
        } else if (KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {
            state = EXTRA;
        }

        break;
       
      case PLAY:
        if (playcounter) {
          //Backgrounds and strings
          drawRectDMA(0, 0, 240, 160, COLOR(0, 0, 0));
          drawRectDMA(140, 0, 240, 30, COLOR(30, 30, 15));
          drawRectDMA(18, 0, 240, 60, COLOR(30, 30, 15));
          drawImageDMA(23, 100, 40, 40, gamecat);
          snprintf(lifeb, 10, "LIFE: %d", life);
          drawString(6, 5, lifeb, COLOR(30, 30, 30));
          drawString(6, 60, "Get that Churu!", COLOR(30, 30, 30));
          drawRectDMA(60, 40, 80, 13, COLOR(30, 30, 30));
          drawString(63, 57, "Die only for Churu...", COLOR(0, 0, 0));

          //playercat
          if (defaultcat) {
          drawImageDMA(playerX, playerY, catwidth, catheight, playercat);
        } else {
          drawImageDMA(playerX, playerY, catwidth, catheight, playercat2);  
        }

          //losecats
          drawImageDMA(120, 70, 20, 20, losecat);
          drawImageDMA(110, 90, 20, 20, losecat);
          drawImageDMA(110, 10, 20, 20, losecat);
          drawImageDMA(96, 30, 20, 20, losecat);
          drawImageDMA(120, 220, 20, 20, losecat);
          drawImageDMA(87, 220, 20, 20, losecat);
          drawImageDMA(115, 200, 20, 20, losecat);
          drawImageDMA(83, 180, 20, 20, losecat);
          drawImageDMA(120, 30, 20, 20, losecat);
          drawImageDMA(120, 50, 20, 20, losecat);
          drawImageDMA(117, 160, 20, 20, losecat);
          drawImageDMA(120, 150, 20, 20, losecat);
          drawImageDMA(81, 130, 20, 20, losecat);    
          drawImageDMA(82, 152, 20, 20, losecat);
          drawImageDMA(116, 120, 20, 20, losecat);
          drawImageDMA(115, 110, 20, 20, losecat);

          // wincats
          drawImageDMA(93, 97, 20, 20, wincat);
          drawImageDMA(81, 0, 20, 20, wincat);
          drawImageDMA(114, 190, 20, 20, wincat);

          // Churu
          drawImageDMA(100, 220, 20, 20, churu);
          playcounter = 0;        
        }
        if (defaultcat) {
          drawImageDMA(playerX, playerY, 10, 10, playercat);
        } else {
          drawImageDMA(playerX, playerY, 10, 10, playercat2);
        }
        

        // Direction keys: left, right, up, down
          if (KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {
            if (playerY >= 5) {
              playerY = playerY - 5;
            }
        
            if (isCollideWithLose(playerX, playerY)) {
              if (life != 0) {
                life--;
              } else {
                state = LOSE;
              }
            }

            if (isCollideWithWin(playerX, playerY)) {
              life++;
            }

            snprintf(lifeb, 10, "LIFE: %d", life);
            drawRectDMA(0, 0, 28, 18, COLOR(0, 0, 0));
            drawString(6, 5, lifeb, COLOR(30, 30, 30));
            

        } else if (KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons)) {
            if (playerY <= 235) {
              playerY = playerY + 5;
            }

            if (isCollideWithLose(playerX, playerY)) {
              if (life != 0) {
                life--;
              } else {
                state = LOSE;
              }
            }

            if (isCollideWithWin(playerX, playerY)) {
              life++;
            }

            snprintf(lifeb, 10, "LIFE: %d", life);
            drawRectDMA(0, 0, 28, 18, COLOR(0, 0, 0));
            drawString(6, 5, lifeb, COLOR(30, 30, 30));

        } else if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {
            if (playerX >= 83) {
              playerX = playerX - 5;
            }

            if (isCollideWithLose(playerX, playerY)) {
              if (life != 0) {
                life--;
              } else {
                state = LOSE;
              }
            }

            if (isCollideWithWin(playerX, playerY)) {
              life++;
            }

            snprintf(lifeb, 10, "LIFE: %d", life);
            drawRectDMA(0, 0, 28, 18, COLOR(0, 0, 0));
            drawString(6, 5, lifeb, COLOR(30, 30, 30));
          
        } else if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {
            if (playerX <= 125) {
              playerX = playerX + 5;
            }

            if (isCollideWithLose(playerX, playerY)) {
              if (life != 0) {
                life--;
              } else {
                state = LOSE;
              }
            }

            if (isCollideWithWin(playerX, playerY)) {
              life++;
            }

            snprintf(lifeb, 10, "LIFE: %d", life);
            drawRectDMA(0, 0, 28, 18, COLOR(0, 0, 0));
            drawString(6, 5, lifeb, COLOR(30, 30, 30));
        }

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          life = 5;
          state = START;
          playerX = 130;
          playerY = 0;
          anicounter = 1;
          startcounter = 1;
          playcounter = 1;
          wincounter = 1;
          losecounter = 1;
          extracounter = 1;
        }

        if (playerX + 10 >= 100 && playerX < 120 && playerY + 10 >= 220 && playerY < 240) {
          state = WIN;    
        }
    
      break;

      case WIN:
        if (wincounter) {
          drawFullScreenImageDMA(winbg);
          drawString(15, 35, "MEOWWWWW... (YOU WIN HUMAN...)", COLOR(0, 0, 0));
          wincounter = 0;
        }

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          life = 5;
          state = START;
          playerX = 130;
          playerY = 0;
          anicounter = 1;
          startcounter = 1;
          playcounter = 1;
          wincounter = 1;
          losecounter = 1;
          extracounter = 1;
        }

        break;

      case LOSE:
        if (losecounter) {
          drawFullScreenImageDMA(losebg);
          drawString(72, 60, "MEOW MEOOW! (YOU LOSE!)", COLOR(0, 0, 0));
          losecounter = 0;
        }
        
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          life = 5;
          state = START;
          playerX = 130;
          playerY = 0;
          anicounter = 1;
          startcounter = 1;
          playcounter = 1;
          wincounter = 1;
          losecounter = 1;
          extracounter = 1;
        }

        break;

        case EXTRA:
          if (extracounter) {
            drawRectDMA(0, 0, 240, 160, COLOR(0, 0, 0));
            drawRectDMA(30, 40, 80, 13, COLOR(30, 30, 30));
            drawString(33, 68, "Choose your cat!", COLOR(0, 0, 0));
            drawImageDMA(43, 50, 70, 70, leftcat);
            drawImageDMA(43, 120, 70, 70, rightcat);
            drawString(120, 54, "Press Left  Press Right", COLOR(30, 30, 30));
            drawString(135, 58, "Press ENTER to Start!", COLOR(30, 5, 21));
            extracounter = 0;
          }

          if (KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {
            defaultcat = 0;
          } else if (KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons)) {
            defaultcat = 1;
          }

          if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          vBlankCounter = 0;
          life = 5;
          state = PLAY;
          }

          if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          life = 5;
          state = START;
          playerX = 130;
          playerY = 0;
          anicounter = 1;
          startcounter = 1;
          playcounter = 1;
          wincounter = 1;
          losecounter = 1;
          extracounter = 1;
        }
            break;
    
    }

    previousButtons = currentButtons; 
  }

  return 0;
}
