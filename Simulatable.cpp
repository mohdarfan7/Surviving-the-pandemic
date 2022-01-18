#include "simulatable.h"

//for virus and character class 
//
Simulatable::Simulatable(bool running){
    this->running = running;
}

int Simulatable::calculate(int groundH){
     //Do vector calculations
     ay += g;
     vy += ay/100;
     //Calculate the current air friction or inertia on x axis
     af = (iaf + abs(vx))/1000;//
     ax -= (y>= groundH)?0:af;
     vx = (ax == -100 || ax == 100)?0:(vx+ax)/10;
     x += vx;
     y += vy;
     //check if our calculations put us below the ground
     if(y <= groundH){
       y = groundH;
       vy = 0;
       ay = g;
       return 0;
     }
     return 1;
}
