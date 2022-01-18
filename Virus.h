#ifndef VIRUS_H
#define VIRUS_H

#include "drawable.h"
#include "simulatable.h"

const int vtFloats = 0;
const int vtHeavy = 1;
const int vtRandom = 2;

class Virus: public Simulatable
{
    public:
        int type;
        Virus(char * file, int type, int W, int H, int groundH);

        void simulate(int groundH);
        void Draw();

    private:
        int state = 0; //0-not present/Visible 1 - Present, -1 = inactive
        unsigned int id;
        static bool imageReady;
        static DrawableBody* image;
        unsigned static int tids;
};


#endif // VIRUS_H
