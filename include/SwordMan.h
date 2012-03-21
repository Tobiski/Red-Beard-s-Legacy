#ifndef SWORDMAN_H
#define SWORDMAN_H

#define DEFENSE 0
#define STRIKE 1

#define UP 2
#define DOWN 3
#define MIDDLE 4
#define DO_NOTHING 666

#include "../include/Drawable.h"
#include "../include/Misc.h"

class SwordMan : public Drawable
{
    public:
        SwordMan(int id);
        virtual ~SwordMan();

        void Update() {}
        void Strike(int dir);
        void Defence(int dir); // if player defens then choise is negative
        void LoseEnergy();
        void Move(int direction);
        void DoNothing();

        void Turn(bool turn);

        bool GetTurn() { return strikeTurn; }
        int GetChoise() { return choise;}

    private:
        int id;
        int choise;
        bool strikeTurn; // 0 defence 1 strike
};

#endif // SWORDMAN_H
