#ifndef SWORDMAN_H
#define SWORDMAN_H

#define DEFENSE 0
#define STRIKE 1

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
        void Strike(int dir);
        void Defence(int dir); // if player defens then choise is negative
        void LoseEnergy();
        void Move(int direction);

        void Turn(bool turn);

        bool GetTurn() { return strikeTurn; }
        int GetChoise() { return choise;}

    private:
        sf::Image image;
        sf::Sprite sprite;
        int choise;
        bool strikeTurn; // 0 defence 1 strike
};

#endif // SWORDMAN_H
