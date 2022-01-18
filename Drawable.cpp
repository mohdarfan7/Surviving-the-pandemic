#include "drawable.h"
#include "2D_graphics.h"
#include <iostream>

DrawableBody::DrawableBody(int nFiles, char* files[], int W, int H){
  this->w = W;
  this->h = H;
  this->frames = new int[nFiles];
  for(int i = 0; i < nFiles;i++){
    std::cout<<"Loading:"<<files[i]<<" -";
    create_sprite(files[i], this->frames[i]);
    std::cout<<"Done!"<<std::endl;
  }
}

void DrawableBody::draw(int x, int y, int frame){
  x = x - (this->ahx*this->w/10);
  y = y - (this->ahy*this->h/10);
  draw_sprite(this->frames[frame], (double)x, (double)y, 0.0, 1.0);
}

Background::Background(char * filename){
    create_sprite(filename, this->sprite);
}

void Background::draw(){
  clear();
  draw_sprite(this->sprite, 0, 0, 0, -1);
}
