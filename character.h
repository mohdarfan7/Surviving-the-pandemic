#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "simulatable.h"
#include "drawable.h"
//using simulatable and drawable classes to build character class 
//nested class concept
//using headers of simulatable and drawable to  call classes in this class
//The role of this class is to introduce movement and graphics of character
class Character: public Simulatable, public DrawableBody{

    int currentSprite = 0;
    short switchingState = 0;
    short state = 0;
    short nState = -10;
    void startJump();
    void switchState(short newState, bool immediate);

    protected:
    public:
        static const short IDLE = 0, MOVEL = -1, MOVER = 1, MOVERR = 2,
            MOVELL = -2, JUMP = 3, FREEFALL = 4, CROUCH = 5, CROUCH2 = 6;
        short getState();
        short getNState();
        short getSState();
        
        Character(int nFrames, char* * files, int W, int H, int groundH);

        bool moveLeft = false, moveRight = false, jump = false, crouch = false;

        void simulate(int gh);
        void Draw();
};

#endif // CHARACTER_H_INCLUDED
