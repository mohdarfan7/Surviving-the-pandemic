#ifndef DRAWABLE_H_
#define DRAWABLE_H_

const int MAXW = 800;
const int MAXH = 600;


class DrawableBody{
  public:
    DrawableBody(int nFiles, char* * files, int W, int H);
    void draw(int x, int y, int frame);


  private:
    int id = 0;
    int ahx = 5, ahy = 10, scale = 1;
    int w = 0, h = 0;
    int offsetX, offsetY;
    int* frames;
};


class Background{
  public:
  Background(char * filename);
  void draw();
  private:
    int sprite;
};

#endif
