#ifndef _CANNONBALL_H_
#define _CANNONBALL_H_

#include <SFML/Graphics.hpp>
#include "../include/Drawable.h"

class ShipEntity;
class Enemy;

class Cannonball : public Drawable
{
private:
    int id;
    float direction;
public:
    Cannonball(float posx, float posy, float direction, int id);
    ~Cannonball();
    void Update();
    bool CheckCollision(ShipEntity &enemy);
    float GetTime()
    {
        return spawnTime.GetElapsedTime();
    }
    int GetId()
    {
        return id;
    }
};

#endif
