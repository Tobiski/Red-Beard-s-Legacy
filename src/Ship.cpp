#include <iostream>
#include "../include/Misc.h"
#include "../include/Ship.h"
#include "../include/Cannonball.h"

#include <algorithm>
namespace ia
{
std::string itoa(int value, int base)
{
    std::string buf;

    buf.reserve( 35 );

    int quotient = value;

    // Translating number to string with base:
    do
    {
        buf += "0123456789abcdef"[ abs( quotient % base ) ];
        quotient /= base;
    }
    while ( quotient );

    // Append the negative sign
    if ( value < 0) buf += '-';

    reverse( buf.begin(), buf.end() );
    return buf;
}
}

Ship::Ship(std::string imageDir, float posx, float posy)
{
    image.LoadFromFile(imageDir);
    image.SetSmooth(false);
    sprite.SetImage(image);
    this->posx = posx;
    this->posy = posy;
    sprite.SetPosition(this->posx, this->posy);
    accel = 0;
    angle = 90;
    sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
    speedx = 0;
    speedy = 0;
    cooldown = 0;
    score = 0;
    health = 5;
    shipsHit = 0;
    cannonballsShot = 0;
    cannonLevel = 1;
    gold = 1000;
}

Ship::~Ship()
{
}

void Ship::Accel(int dir)
{
    switch(dir)
    {
    case 0:
        if(accel < 1)
        {
            accel = accel + 0.01;
        }
        else
        {
            accel = 1;
        }
        break;
    case 1:
        if(accel > 0.05)
        {
            accel = accel - 0.005;
        }
        else
        {
            accel = 0.05;
        }
        break;
    }
}

void Ship::Turn(int dir)
{
    switch(dir)
    {
    case 0:
        angle++;
        if(angle > 360)
        {
            angle = 0;
        }
        break;
    case 1:
        angle--;
        if(angle < 0)
        {
            angle = 360;
        }
    }
}

void Ship::Update()
{
    speedx = accel * sin(angle*3.14159265/180);
    speedy = accel * cos(angle*3.14159265/180);

    if(posx+ speedx > 0 && posx+ speedx < WIN_WIDTH)
    {
        posx = posx + speedx;
    }

    if(posy+ speedy*-1 > 0 && posy+ speedy*-1 < WIN_HEIGHT)
    {
        posy = posy + speedy*-1;
    }

    if(cooldown > 0)
    {
        cooldown--;
    }

    sprite.SetRotation(angle*-1);
    sprite.SetPosition(posx, posy);
}

void Ship::Fire(std::vector<Cannonball*> &cannonballs)
{
    if(cooldown == 0)
    {
        cooldown = 80;
        cannonballsShot++;
        cannonballs.push_back(new Cannonball(posx, posy, (angle+90), PLAYER));
    }
}

std::string Ship::GetScore()
{
    std::string scoreString = "Score: ";
    std::string points  = ia::itoa(score, 10);
    scoreString += points;

    return scoreString;
}

std::string Ship::GetGoldString()
{
    std::string goldString = "Gold: ";
    std::string goldAdd  = ia::itoa(gold, 10);
    goldString += goldAdd;

    return goldString;
}

std::string Ship::GetInfo()
{
    std::string info1 = "You shot ";
    std::string info2 = " cannonballs";

    if(cannonballsShot != 0)
        accuracy = (float)shipsHit / (float)cannonballsShot * 100;

    std::string shots = ia::itoa(cannonballsShot, 10);
    info1 += shots;
    info1 += info2;
    info1 += "\nYour accuracy was ";

    std::string acc = ia::itoa(accuracy, 10);
    info1 += acc;
    info1 += " %";

    return info1;
}

bool Ship::RemoveGold(int amount)
{
    if(gold >= amount)
    {
        gold -= amount;
        return true;
    }
    else
    {
        return false;
    }
}
