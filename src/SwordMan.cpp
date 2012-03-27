#include "../include/SwordMan.h"
SwordMan::SwordMan(int id)
{
    //cto
    if(id == PLAYER)
        image.LoadFromFile("images/swordMan.png");
    else
        image.LoadFromFile("images/enemySwordMan.png");
    image.SetSmooth(false);
    sprite.SetImage(image);
    this->id = id;
    if(id == PLAYER)
    {
        posx = WIN_WIDTH / 2 - 200;
        posy = 477 - sprite.GetSize().y;
    }
    else
    {
        posx = WIN_WIDTH / 2 + 200;
        posy = 477 - sprite.GetSize().y;
    }
    health = 5;
    sprite.SetPosition(posx, posy);
}

SwordMan::~SwordMan()
{
    //dtor
}

void SwordMan::Move(int direction)
{
    if(direction == RIGHT)
        posx++;
    else
        posx--;

    sprite.SetPosition(posx, posy);
}

void SwordMan::DoNothing()
{
    choise = DO_NOTHING;
}

void SwordMan::Strike(int dir)
{
    if(dir > 1)
        choise = dir;
    else
        Move(dir);
}

void SwordMan::Defence(int dir)
{
    if(dir > 1)
        choise = -dir;
    else
        Move(dir);
}

void SwordMan::Turn(bool turn)
{
    strikeTurn = turn;
}


