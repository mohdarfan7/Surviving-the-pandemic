#include "character.h"
//#include <cstdio>

void Character::startJump(){
    switchState(JUMP, (nState == JUMP)?false:true);
    ay = 200 - g;
}

//void from character header
short Character::getState(){
    return state;//state
}

short Character::getNState(){
    return nState;//newstate
}

short Character::getSState(){
    return switchingState;//switchingstate
}
//
void Character::switchState(short newState, bool immediate){
    if(!immediate){
        if(switchingState > 0){
            switchingState--;
            return;
        }else if(nState != -10){
            if(this->nState == newState){
              this->state = nState;
              nState = -10;
            }
            else{
              this->state = nState;
              nState = newState;
            }
            switchingState = 0;
            return;
        }
        else if(newState == -10){
            return;
        }
    }
    else{
        switchingState = 0;
        nState = newState;
        return;
    }
    nState = newState;
    if(this->state==IDLE){
        switchingState = 0;
    }
    else if(this->state==JUMP){
        switchingState = 1;
    }
    else if(this->state == CROUCH || this->state == CROUCH2){
        if(newState == CROUCH2) switchingState = 3;
        else if(newState == IDLE) switchingState = 3;
        else switchingState = 0;
    }
    else if(this->state == MOVER || this->state == MOVEL){
        if(this->state == newState) switchingState = 0;
        else{
            if(newState == MOVERR || newState == MOVELL) switchingState = 5;
            else switchingState = 1;
        }
    }
    else if( this->state == MOVERR || this->state == MOVELL){
        if(this->state == newState) switchingState = 0;
        else{
            if(this-> state == MOVER || this->state == MOVEL) switchingState = 5;
            else switchingState = 1;
        }
    }
    else{
        switchingState = 0;
    }
}
//
Character::Character(int nFrames, char* * files, int W, int H, int groundH): Simulatable(true), DrawableBody(nFrames, files, W, H){
    this->state = 0;
    this->x = 20;
    this->y = groundH;
    this->ay = -g;
}

void Character::simulate(int groundH){
    //printf("nState:%d ", nState);used to verify 
    switchState(nState, false); //Switch if we needprevious state setting
    //printf("nState:%d ", nState);
  //Process and reset inputs, used  logic-set state, did  physics calculations, set sprites
    switch(state){
       case IDLE:
         this->currentSprite = 0;
         if(jump) startJump();
         else if(crouch) switchState(CROUCH, false);
         if(moveLeft){
           moveLeft = false;
           if(!jump && !crouch) switchState(MOVEL, false);
           this->ax = -30;
         } else if(moveRight){
           moveRight = false;
           if(!jump && !crouch) switchState(MOVER, false);
           this->ax = 30;
         }
         //printf("nState:%d ", nState);
         break;
       case MOVER:
           switchState(MOVERR, false);
       case MOVERR:
          if(jump) startJump();
          else if(crouch) switchState(CROUCH, true);
          else this->currentSprite = (this->state==MOVER)?1:2;
          if(!moveRight){ //We should stop moving
            ax = -100; //signal that we need to stop
            switchState(IDLE, true);
          }
          if(this->state == MOVERR) switchState(MOVER, false);
          break;
       case MOVEL:
           switchState(MOVELL, false);
       case MOVELL:
         if(jump) startJump();
         else if(crouch) switchState(CROUCH, true);
         else this->currentSprite = (this->state==MOVEL)?4:3;
         if(!moveLeft){
           ax = 100;
           switchState(IDLE, true);
         }
         else if(this->state == MOVELL) switchState(MOVEL, false);
         break;
       case JUMP: //We're jumping up!
         currentSprite = 0;
         if(jump) jump = false; //Can't jump while already jumping!!
         if(moveLeft){ //Can fly!
           moveLeft = false;
           ax = (ax >= 0)?-20:ax;
         }else if(moveRight){ //Can Fly!
           moveRight = false;
           ax = (ax <= 0)?20:ax;
         }
         if(vy <= 0) switchState(FREEFALL, true);
         break;
       case FREEFALL: //FreeFall
         if(jump) jump = false;
         //switchState(IDLE, false);
         //ay = g;
         break;
       case CROUCH:
         currentSprite = 6;
         if(!crouch){
           switchState(CROUCH2, false);
         }
         jump = (jump)?false:jump;
         if(moveLeft){
           moveLeft = false;
           ax = (ax >= 0)?-10:ax;
         }else if(moveRight){
           moveRight = false;
           ax = (ax <= 0)?10:ax;
         }
         break;
       case CROUCH2:
           currentSprite = 5;
           switchState(IDLE, false);
           if(!moveRight){ //We should stop moving
            ax = -100; //signal that we need to stop
           }
           if(!moveLeft){
            ax = 100;
           }
     }
     crouch = (crouch)?false:crouch;
     jump = (jump)?false:jump;
     if(calculate(groundH)==0 && this->state==FREEFALL){
       if(vx > 0) switchState(MOVER, true);
       else if (vx < 0) switchState(MOVEL, true);
       else switchState(IDLE, true);
     }
     //printf("nState:%d \n", nState);
}

void Character::Draw(void){
    this->draw(this->x, this->y, currentSprite);
}
