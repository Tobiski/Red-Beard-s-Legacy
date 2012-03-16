#include "../include/Cannonball.h"
#include "../include/Enemy.h"
#include "../include/Misc.h"

Cannonball::Cannonball(float posx, float posy, float direction, int id)
{
    this->id = id;
    image.LoadFromFile("images/cannonball.png");
    image.SetSmooth(false);
    sprite.SetImage(image);
    this->posx = posx;
    this->posy = posy;
    this->direction = direction;
    sprite.SetPosition(this->posx, this->posy);
    spawnTime.Reset();
}

Cannonball::~Cannonball()
{
}

void Cannonball::Update()
{
    posx += 4*sin(direction*3.14159265/180);
    posy += 4*cos(direction*3.14159265/180)*-1;

    sprite.SetPosition(posx, posy);
}

void Cannonball::Draw(sf::RenderWindow& window)
{
    window.Draw(sprite);
}

bool Cannonball::CheckCollision(ShipEntity &enemy)
{
    if(posx + sprite.GetSize().x > enemy.GetXpos() - (enemy.GetWidth()/2) &&
            posx < enemy.GetXpos() + enemy.GetWidth() - (enemy.GetWidth()/2) &&
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

int Cannonball::GetArea()
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
