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


