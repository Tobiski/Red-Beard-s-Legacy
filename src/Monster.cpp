#include "../include/Monster.h"
#include "../include/Misc.h"

Monster::Monster()
{
    // Create a monster type
    switch(rand()%3)
    {
        case OCTOPUSSY:
            monsterType = OCTOPUSSY;
            image.LoadFromFile("/media/GigaStorage/Pictures/oct.jpg");
            break;
        case SNAKE:
            monsterType = SNAKE;
            image.LoadFromFile("/media/GigaStorage/Pictures/oct.jpg");
            break;
        case JELLYFISH:
            monsterType = JELLYFISH;
            image.LoadFromFile("/media/GigaStorage/Pictures/oct.jpg");
            break;
    }

    image.SetSmooth(false);
    sprite.SetImage(image);

    // Create a random place for monster
    posx = rand()%WIN_WIDTH-1;
    posy = rand()%WIN_HEIGHT-1;
    sprite.SetPosition(posx,posy);
}

Monster::~Monster()
{

}
