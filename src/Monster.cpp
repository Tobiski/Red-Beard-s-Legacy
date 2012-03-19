#include "../include/Monster.h"
#include "../include/Misc.h"
#include "../include/ShipEntity.h"
#include "../include/Animation.h"
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

    spawning = true;
    spawnAnimation = new Animation(posx, posy, 0, "images/monsterSpawnAnimation.png", 20);
}

Monster::~Monster()
{
}

void Monster::Update(float playerX, float playerY)
{
    if(!spawning)
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
    else
    {
        spawnAnimation->Update();
        if(spawnAnimation->GetCurrentFrame() == spawnAnimation->GetMaxFrames())
        {
            delete spawnAnimation;
            spawning = false;
        }
    }
}

bool Monster::CheckCollision(ShipEntity &enemy)
{
    if(!spawning)
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
    else
    {
        return false;
    }
}

void Monster::DrawSpawningAnimation(sf::RenderWindow &ewindow)
{
    spawnAnimation->Draw(ewindow);
}
