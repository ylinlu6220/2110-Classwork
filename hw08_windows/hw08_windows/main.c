#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"
#include "images/title.h"
#include "images/bird.h"
#include "images/fries.h"
#include "images/fruitTart.h"
#include "images/wing.h"
#include "images/noods.h"
#include "images/dew.h"
#include "images/water.h"
#include "images/lose.h"
#include "images/win.h"
#include "images/f1.h"
#include "images/f2.h"
#include "images/f3.h"
#include "images/f4.h"

/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  SSTART,
  START,
  MAP,
  MAP1,
  MAP2,
  MAP3,
  MAP4,
  PLAY,
  WIN,
  LOSE,
};

void delay(int n){
  volatile int x = 0;
  for (int i = 0; i<n*8000; i++) {
    x++;
  }
}

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = SSTART;
  char line[20];
  struct bird player;
  player.hp = 1;
  player.score = 0;
  player.x = 100;
  player.y = 100;
  int lvl = 1;
  int ani=5;

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    waitForVBlank();
    switch (state) {
      case SSTART:
        drawFullScreenImageDMA(Title);
        state = START;
        break;
      case START:

        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) { //start game to map
          state = MAP;
        }

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
          drawString(5, 5, "restarted", BLACK);
          player.hp = 1;
          player.score = 0;
          player.x = 100;
          player.y = 100;
          lvl = 1;
        }
        
        if (ani < 100) {
          undrawImageDMA(88, ani, 79, 72, f1);
          drawImageDMA(88, ani, 79, 72, f1);
          if (KEY_DOWN(BUTTON_START, currentButtons)) { //start game to map
            state = MAP;
          }

          if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
            drawString(5, 5, "restarted", BLACK);
            player.hp = 1;
            player.score = 0;
            player.x = 100;
            player.y = 100;
            lvl = 1;
          }
          delay(6);
          ani++;
          undrawImageDMA(88, ani, 79, 72, f2);
          drawImageDMA(88, ani, 79, 72, f2);
          if (KEY_DOWN(BUTTON_START, currentButtons)) { //start game to map
            state = MAP;
          }

          if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
            drawString(5, 5, "restarted", BLACK);
            player.hp = 1;
            player.score = 0;
            player.x = 100;
            player.y = 100;
            lvl = 1;
          }
          delay(6);
          ani++;
          undrawImageDMA(88, ani, 79, 72, f3);
          drawImageDMA(88, ani, 79, 72, f3);
          if (KEY_DOWN(BUTTON_START, currentButtons)) { //start game to map
            state = MAP;
          }

          if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats 
            drawString(5, 5, "restarted", BLACK);
            player.hp = 1;
            player.score = 0;
            player.x = 100;
            player.y = 100;
            lvl = 1;
          }
          delay(6);
          ani++;
          undrawImageDMA(88, ani, 79, 72, f1);
          drawImageDMA(88, ani, 79, 72, f1);
          if (KEY_DOWN(BUTTON_START, currentButtons)) { //start game to map
            state = MAP;
          }

          if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
            drawString(5, 5, "restarted", BLACK);
            player.hp = 1;
            player.score = 0;
            player.x = 100;
            player.y = 100;
            lvl = 1;
          }
          delay(6);
          ani++;
          undrawImageDMA(88, ani, 79, 72, f4);
          drawImageDMA(88, ani, 79, 72, f4);
          if (KEY_DOWN(BUTTON_START, currentButtons)) { //start game to map
            state = MAP;
          }

          if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
            drawString(5, 5, "restarted", BLACK);
            player.hp = 1;
            player.score = 0;
            player.x = 100;
            player.y = 100;
            lvl = 1;
          }
          delay(6);
        } else {
          undrawImageDMA(88, ani, 79, 72, f1);
          drawImageDMA(88, ani, 79, 72, f1);
          if (KEY_DOWN(BUTTON_START, currentButtons)) { //start game to map
            state = MAP;
          }

          if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
            drawString(5, 5, "restarted", BLACK);
            player.hp = 1;
            player.score = 0;
            player.x = 100;
            player.y = 100;
            lvl = 1;
          }
          delay(6);
          ani--;
          undrawImageDMA(88, ani, 79, 72, f2);
          drawImageDMA(88, ani, 79, 72, f2);
          if (KEY_DOWN(BUTTON_START, currentButtons)) { //start game to map
            state = MAP;
          }

          if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
            drawString(5, 5, "restarted", BLACK);
            player.hp = 1;
            player.score = 0;
            player.x = 100;
            player.y = 100;
            lvl = 1;
          }
          delay(6);
          ani--;
          undrawImageDMA(88, ani, 79, 72, f3);
          drawImageDMA(88, ani, 79, 72, f3);
          delay(6);
          if (KEY_DOWN(BUTTON_START, currentButtons)) { //start game to map
            state = MAP;
          }

          if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
            drawString(5, 5, "restarted", BLACK);
            player.hp = 1;
            player.score = 0;
            player.x = 100;
            player.y = 100;
            lvl = 1;
          }
          ani--;
          undrawImageDMA(88, ani, 79, 72, f1);
          drawImageDMA(88, ani, 79, 72, f1);
          if (KEY_DOWN(BUTTON_START, currentButtons)) { //start game to map
            state = MAP;
          }

          if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
            drawString(5, 5, "restarted", BLACK);
            player.hp = 1;
            player.score = 0;
            player.x = 100;
            player.y = 100;
            lvl = 1;
          }
          delay(6);
          ani--;
          undrawImageDMA(88, ani, 79, 72, f4);
          drawImageDMA(88, ani, 79, 72, f4);
          if (KEY_DOWN(BUTTON_START, currentButtons)) { //start game to map
            state = MAP;
          }

          if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
            drawString(5, 5, "restarted", BLACK);
            player.hp = 1;
            player.score = 0;
            player.x = 100;
            player.y = 100;
            lvl = 1;
          }
          delay(6);
        }

        break;
      case MAP:
        fillScreenDMA(GRAY);
        
        state = MAP1;
        break;
      case MAP1:
        snprintf(line, sizeof(line), "Score: %d", player.score);
        drawString(5, 180, line, WHITE);
        snprintf(line, sizeof(line), "HP: %d", player.hp);
        drawString(15, 180, line, WHITE);

        if (lvl == 1) {
          state = MAP2;
        } else if (lvl == 2) {
          state = MAP3;
        } else if (lvl == 3) {
          state = MAP4;
        }
        break;
      case MAP2:      
        drawString(5, 5, "Snoopy is craving something", WHITE);
        drawString(15, 5, "salty and crunchy!", WHITE);
        drawImageDMA(50, 25, 50, 50, fries);
        drawImageDMA(50, 150, 50, 50, fruitTart);
        
        drawImageDMA(player.x, player.y, 50, 50, bird);

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
          state = SSTART;
        }
        
        state = PLAY;
        break;
      case MAP3:
        drawString(5, 5, "Snoopy is craving something", WHITE);
        drawString(15, 5, "fizzy and gamer!", WHITE);
        drawImageDMA(50, 25, 50, 50, water);
        drawImageDMA(50, 150, 50, 50, dew);
        
        
        player.x = 100;
        player.y = 100;
        drawImageDMA(player.x, player.y, 50, 50, bird);
        waitForVBlank();

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
          state = SSTART;
        }

        state = PLAY;
        break;
      case MAP4:
        drawString(5, 5, "Snoopy is craving something", WHITE);
        drawString(15, 5, "juicy and fried!", WHITE);
        drawImageDMA(50, 25, 50, 50, wing);
        drawImageDMA(50, 150, 50, 50, noods);
        
        
        player.x = 100;
        player.y = 100;
        drawImageDMA(player.x, player.y, 50, 50, bird);
        waitForVBlank();

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
          state = SSTART;
        }

        state = PLAY;
        break;
      case PLAY:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
            state = SSTART;
          }

        if(KEY_DOWN(BUTTON_UP, currentButtons)) { // if bird goes up
            undrawImageDMA(player.x, player.y, 50, 50, bird);
            drawRectDMA(player.x, player.y, 50, 50, GRAY);
            player.x --;
            drawImageDMA(player.x, player.y, 50, 50, bird);
        }
        if(KEY_DOWN(BUTTON_DOWN, currentButtons)) { // if bird goes up
            undrawImageDMA(player.x, player.y, 50, 50, bird);
            drawRectDMA(player.x, player.y, 50, 50, GRAY);
            player.x ++;
            drawImageDMA(player.x, player.y, 50, 50, bird);
        }
        if(KEY_DOWN(BUTTON_RIGHT, currentButtons)) { // if bird goes up
            undrawImageDMA(player.x, player.y, 50, 50, bird);
            drawRectDMA(player.x, player.y, 50, 50, GRAY);
            player.y ++;
            drawImageDMA(player.x, player.y, 50, 50, bird);
        }
        if(KEY_DOWN(BUTTON_LEFT, currentButtons)) { // if bird goes up
            undrawImageDMA(player.x, player.y, 50, 50, bird);
            drawRectDMA(player.x, player.y, 50, 50, GRAY);
            player.y --;
            drawImageDMA(player.x, player.y, 50, 50, bird);
        }
        
        // state = ?
        if (lvl % 2 == 1) {
          if(player.x < 100 && player.x > 50 && player.y < 75){
            player.score++;
            lvl ++;
            state = MAP;
            if (player.score == 3) {
              state = WIN;
            }
          }
          else if (player.x < 100 && player.x > 50 && player.y > 125){
            player.hp--;
            if (player.hp > 0){
              state = MAP;
            } else{
              state = LOSE;
            }
          }
        } else {
          if(player.x < 100 && player.x > 50 && player.y < 75){
            player.hp--;
            if (player.hp > 0){
              state = MAP;
            } else{
              state = LOSE;
            }
          }
          else if (player.x < 100 && player.x > 50 && player.y > 125){
            player.score++;
            lvl ++;
            state = MAP;
            if (player.score == 3) {
              state = WIN;
            }
          }
        }
        break;
      case WIN:
        drawFullScreenImageDMA(win);
        player.hp = 1;
        player.score = 0;
        player.x = 100;
        player.y = 100;
        lvl = 1;

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
          state = SSTART;
        }

        // state = ?
        break;
      case LOSE:
        drawFullScreenImageDMA(lose);
        player.hp = 1;
        player.score = 0;
        player.x = 100;
        player.y = 100;
        lvl = 1;

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)){ //reset stats
          state = SSTART;
        }
        // state = ?
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}