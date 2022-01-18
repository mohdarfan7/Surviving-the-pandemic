#include "Virus.h"
#include <cstdlib>

unsigned int Virus::tids = 0;
bool Virus::imageReady = false;
DrawableBody* Virus::image;

Virus::Virus(char * file, int type, int W, int H, int groundH): Simulatable(false)
{
    this->id = this->tids++;
    this->type = type;
    x = rand() % (MAXW-100) + 90;
    y = rand() % (MAXH) + groundH;
    if(type == vtRandom) this->running = true;
    else if(type == vtHeavy){
        this->running = true;
        this->state = 1;
    }
    else{
        this->state = 1; //Draw always
    }
    if(!this->imageReady){
        this->imageReady = true;
        this->image = new DrawableBody(1, &file, W, H);
    }
}

void Virus::simulate(int groundH){
    if (!this->running) return; //Floaters need no SIM
    if(type == vtRandom){
        if(state == 0){
            x = rand() % (MAXW-100) + 50;
            y = rand() % (MAXH) + groundH;
            if(rand() % 10 >= 5) state = 1;
        }
        else{
            if(rand() % 10 >= 5){ //Change velocity at random
                ax = rand() % 350 - 150;
                ay = rand() % (-g*3) + g/2;
            }
        }
    }
    if(this->calculate(groundH)==0){
        if(type == vtRandom) { //Randoms will appear again!
            state = 0;
            return;
        }
        this->running = false;
        this->state = -1;
    }
    if(y <= 0) ay = -ay;
    if(x <= 0) ax = -ax;
}

void Virus::Draw(){
    if(state == 1 || state == -1) this->image->draw(x, y, 0);
}
