// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"//precompilation google


#include <iostream>
#include <cstdio>
#include <cmath>

#include <Windows.h> // also needed for the 2D graphics library

#include "2D_graphics.h" // use the 2D graphics library

#include "timer.h" // use the time / clock reading function
#include "character.h"
#include "Virus.h"

using namespace std;

char* sprites[] = { "adventurer-idle-03.png", "adventurer-run-04.png", "adventurer-run-03.png", "adventurer-run-04L.png", "adventurer-run-03L.png", "adventurer-crouch-03.png", "adventurer-crouch-01.png" };
char* viruss = { "gvirus.png" };

char* backfile = "dribbleback.png";
//PC: https://dribbble.com/shots/11896136-Classic-City-Game-Background
//Googled!

const short nViruses = 20;

Character* player;
Virus* vparticles[nViruses];

const int groundH = 150;
unsigned int ts = 0, oldt = 0, dt = 0;
short gameState = 0;

void showStats() {
    cout << " STATE:" << player->getState() << " -> " << player->getNState() << ":" << player->getSState() << " X:" << player->x << " Y:" << player->y <<
        " VX:" << player->vx << " VY:" << player->vy << " AX:" << player->ax << " AY:" << player->ay << " J:"
        << player->jump << " C:" << player->crouch << " L:" << player->moveLeft << " R:" << player->moveRight << endl;
}

int main(void)
{
    // note: you have to double click the DirectX_window.exe
    // program in the DirectX_window folder before compiling
    // and running this example

    // the window size can be adjusted in the window_size.txt
    // file inside the DirectX_window folder

    // you need to call the initialize_graphics() function
    // once before using the 2D graphics library
    initialize_graphics();
    oldt = high_resolution_count();
    clear();
    cout << "Starting to load sprites!" << endl;
    player = new Character(7, sprites, 50, 37, groundH);//Character class
    player->y = groundH;
    cout << "done loading char!" << endl;
    for (int i = 0; i < nViruses; i++) {
        vparticles[i] = new Virus(viruss, rand() % 3, 32, 32, groundH);//Virus class 
    }
    cout << "Done loading Viruses!" << endl;
    Background* back = new Background(backfile);
    //whats happens when key are used
    while (!(KEY(VK_ESCAPE))) {
        ts = high_resolution_count();//timer cpp. 
        dt = ts - oldt;
        if (dt <= 159900) continue; //159900 microseconds
        oldt = ts;
        if (KEY(VK_LEFT)) player->moveLeft = true;
        else player->moveLeft = false;
        if (KEY(VK_RIGHT)) player->moveRight = true;
        else player->moveRight = false;
        if (KEY(VK_SPACE)) player->jump = true;
        else if (KEY(VK_CONTROL)) player->crouch = true;
        clear();
        //cout << "Starting Simulation!\n";
        //showStats();
        player->simulate(groundH);
        //showStats();
        int lX, rX, tY, bY;
        back->draw();
        for (int i = 0; i < nViruses; i++) {
            vparticles[i]->simulate(groundH);
            vparticles[i]->Draw();
            lX = vparticles[i]->x - 14;
            rX = vparticles[i]->x + 14;
            tY = vparticles[i]->y + 14;
            bY = vparticles[i]->y - 14;
            //Check simple collisions
            //using classes from Character header and cpp 
            if (player->x >= lX && player->x <= rX && player->y >= bY && player->y <= tY) {
                if(vparticles[i]->type == vtHeavy || vparticles[i]->type == vtFloats)
                    gameState = -1; //Die if we hit a heavy virus or a floating virus..
                else if(player->getState() == player->CROUCH || player->getState() == player->CROUCH2) gameState = 15;
                else gameState = 70;
            }
            //cout << "v"<<i<<endl;
        }
        //cout << "Finished virus draw calls!\n";
        player->Draw();
        if (gameState == -1) {
            cout << "So Careless of youuu  ! Now you are Infected!!" << endl;
            text("Uh OH! Off to the quarantine!", 50, 450, 1.1);
            update();
            break;
        }
        else if (gameState > 0) {
            cout << "Good thing you have a mask! Still follow safety protocols." << endl;
            text("Avoid Socializing and follow safety protocols!", 100, 650, 1.1);
            gameState--;
        }
        //cout << "Starting draw!\n";
        if (player->x >= MAXW) {
            cout << "We reached homed!" << endl;
            text("You're Safe! GAME OVER", 50, 450, 1.1);
            update();
            break;
        }
        
       // call the update() function when you want to view
       // the current drawing in the DirectX graphics window
        update();
        //cout << "Screen updated!" << endl;
    }
   

    cout << "\ndone.\n";
    //getchar();

    return 0;
}



