#ifndef SIMULATABLE_H_
#define SIMULATABLE_H_

#include <cstdlib>

const int iaf = 1;
const int g = -25; // g/4 here for slower gravity

class Simulatable{
  public:
      Simulatable(bool running);
      int x = 0, y = 0;
      int vx = 0, vy = 0, ax = 0, ay = 0;

      int calculate(int groundH);

      virtual void simulate(int groundH){};

  protected:
      bool running  = true;

  private:
      int af = 0;
};

#endif
