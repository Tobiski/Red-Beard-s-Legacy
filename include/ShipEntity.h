#ifndef _SHIPENTITY_H_
#define _SHIPENTITY_H_

#include <SFML/Graphics.hpp>
#include "../include/Drawable.h"

class Cannonball;

class ShipEntity : public Drawable
{
protected:
public:
    ShipEntity() {};
    ~ShipEntity() {};
    virtual void Turn() {};
    virtual void Turn(int dir) {};
    virtual void Fire(std::vector<Cannonball*> &cannonballs) = 0;
    int GetHealth()
    {
        return health;
    }
    void GetHit()
    {
        health--;
    }
    bool CheckCollision(ShipEntity &ship);
};

#endif
