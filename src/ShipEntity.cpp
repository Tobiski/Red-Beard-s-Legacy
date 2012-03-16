#include <SFML/Graphics.hpp>
#include "../include/ShipEntity.h"
#include "../include/Misc.h"

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
