#include "../include/Monster.h"
#include "../include/Misc.h"
#include <iostream>

Monster::Monster()
{
    // Choose a monster type
    switch(rand()%3)
    {
        case OCTOPUSSY:
            monsterType = OCTOPUSSY;
            image.LoadFromFile("images/octopus.png");
            break;
        case SNAKE:
            monsterType = SNAKE;
            image.LoadFromFile("images/octopus.png");
            break;
        case JELLYFISH:
            monsterType = JELLYFISH;
            image.LoadFromFile("images/octopus.png");
            break;
    }

    image.SetSmooth(false);
    sprite.SetImage(image);

    // Choose a random place for monster
    posx = rand()%WIN_WIDTH;
    posy = rand()%WIN_HEIGHT;
    sprite.SetPosition(posx,posy);
    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);

    accelState = INCREASE;
    accel = 0;
    angle = 0;
    speedx = 0;
    speedy = 0;
    if(monsterType == OCTOPUSSY) health = 2;
    else if(monsterType == SNAKE) health = 1;
    else health = 1;
}

Monster::~Monster()
{
}

void Monster::Update(float playerX, float playerY)
{
    switch(monsterType)
    {
        case OCTOPUSSY:
            if(playerX > posx) posx++;
            else posx--;

            if(playerY > posy) posy++;
            else posy--;

            break;
        case SNAKE:
            if(playerX > posx) posx++;
            else posx--;

            if(playerY > posy) posy++;
            else posy--;
            break;
        case JELLYFISH:
            if(accelState == INCREASE)
            {
                if(accel < 2)
                    accel += 0.1;
                else
                    accelState = DECREASE;
            }
            else
            {
                if(accel > 0)
                    accel -= 0.1;
                else
                    accelState = INCREASE;
            }

            if(playerX > posx)
                posx += accel;
            else
                posx -= accel;

            if(playerY > posy)
                posy += accel;
            else
                posy -= accel;
            break;
    }


    sprite.SetPosition(posx, posy);
}
