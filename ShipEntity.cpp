#include <SFML/Graphics.hpp>
#include "ShipEntity.h"
#include "Misc.h"

bool ShipEntity::CheckCollision(ShipEntity &enemy)
{
    if(posx + sprite.GetSize().x > enemy.GetXpos() - (enemy.GetWidth()/2) &&
            posx< enemy.GetXpos() + enemy.GetWidth() - (enemy.GetWidth()/2) &&
            posy + sprite.GetSize().y > enemy.GetYpos() - (enemy.GetHeight()/2) &&
            posy < enemy.GetYpos() + enemy.GetHeight() - (enemy.GetHeight()/2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int ShipEntity::GetArea()
{
    if(posx < WIN_WIDTH / 2 && posy < WIN_HEIGHT / 2)
    {
        return 0;
    }
    else if(posx > WIN_WIDTH / 2 && posy < WIN_HEIGHT / 2)
    {
        return 1;
    }
    else if(posx < WIN_WIDTH / 2 && posy > WIN_HEIGHT / 2)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}
