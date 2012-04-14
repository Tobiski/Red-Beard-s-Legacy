#include <iostream>
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

void Drawable::SetDrawArea(int maxFrames, int frame)
{
    sf::IntRect drawArea(frame*160, 0, frame*160+160, sprite.GetSize().y);
    sprite.SetSubRect(drawArea);
}

double Drawable::GetDistance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow((x1-x2),2) + pow((y1-y2),2));
}
