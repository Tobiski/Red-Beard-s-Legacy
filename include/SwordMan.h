#ifndef SWORDMAN_H
#define SWORDMAN_H

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define MIDDLE 4

#include "../include/Drawable.h"

class SwordMan : public Drawable
{
    public:
        SwordMan();
        virtual ~SwordMan();

        void Update() {}
        int GetChoise() { return choise;}
        void Strike(int dir) { choise = dir;  }
        void Defence(int dir) { choise = -dir; } // if player defens then int is negative
        void LoseEnergy() {}
        void Move(int direction);
    private:
        sf::Image image;
        sf::Sprite sprite;
        int choise;
};

#endif // SWORDMAN_H
