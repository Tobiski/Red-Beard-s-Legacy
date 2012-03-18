#include "../include/Monster.h"
#include "../include/Misc.h"
#include <iostream>

Monster::Monster()
{
    // Create a monster type
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

    // Create a random place for monster
    posx = rand()%WIN_WIDTH-1;
    posy = rand()%WIN_HEIGHT-1;
    sprite.SetPosition(posx,posy);
    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);

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
    if(playerX > posx) posx++;
    else posx--;

    if(playerY > posy) posy++;
    else posy--;

    sprite.SetPosition(posx, posy);
}

