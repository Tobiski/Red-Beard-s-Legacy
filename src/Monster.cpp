#include "../include/Monster.h"
#include "../include/Misc.h"

Monster::Monster()
{
    // Create a monster type
    switch(rand()%3)
    {
        case OCTOPUSSY:
            monsterType = OCTOPUSSY;
            image.LoadFromFile("images/octupus.png");
            break;
        case SNAKE:
            monsterType = SNAKE;
            image.LoadFromFile("images/octupus.png");
            break;
        case JELLYFISH:
            monsterType = JELLYFISH;
            image.LoadFromFile("images/octupus.png");
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
    if(monsterType == OCTOPUSSY) health = 5;
    else if(monsterType == SNAKE) health = 4;
    else health = 3;
}

Monster::~Monster()
{
}

void Monster::Update() {
}

