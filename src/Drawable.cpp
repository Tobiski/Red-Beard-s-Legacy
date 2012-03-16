#include "../include/Drawable.h"
#include "../include/Misc.h"

Drawable::Drawable()
{
}

Drawable::~Drawable()
{
}

void Drawable::Draw(sf::RenderWindow &window)
{
    window.Draw(sprite);
}

int Drawable::GetArea()
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
