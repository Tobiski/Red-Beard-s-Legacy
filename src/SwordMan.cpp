#include "../include/SwordMan.h"

SwordMan::SwordMan()
{
    //ctor
}

SwordMan::~SwordMan()
{
    //dtor
}

void SwordMan::Move(int direction)
{
    if(direction == LEFT)
        posx--;
    else
        posx++;
}

void SwordMan::LoseEnergy()
{

}

void SwordMan::Strike(int dir)
{
     choise = dir;
}

void SwordMan::Defence(int dir)
{
     choise = -dir;
}

void SwordMan::Turn(bool turn)
{
    strikeTurn = turn;
}


