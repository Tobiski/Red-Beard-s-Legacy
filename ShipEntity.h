#ifndef _SHIPENTITY_H_
#define _SHIPENTITY_H_

#include <SFML/Graphics.hpp>

class Cannonball;

class ShipEntity
{
protected:
    sf::Image image;
    sf::Sprite sprite;
    float posx;
    float posy;
    float accel;
    float speedx;
    float speedy;
    float rotationAngle;
    int health;
public:
    ShipEntity() {};
    ~ShipEntity() {};
    void Draw(sf::RenderWindow& window);
    virtual void Update() = 0;
    virtual void Turn() {};
    virtual void Turn(int dir) {};
    virtual void Fire(std::vector<Cannonball*> &cannonballs) = 0;
    float GetXpos()
    {
        return posx;
    }
    float GetYpos()
    {
        return posy;
    }
    float GetAccel()
    {
        return accel;
    }
    float GetRotation()
    {
        return rotationAngle;
    }
    int GetHeatlth()
    {
        return health;
    }
    float GetWidth()
    {
        return sprite.GetSize().x;
    }
    float GetHeight()
    {
        return sprite.GetSize().y;
    }
    void GetHit()
    {
        health--;
    }
    bool CheckCollision(ShipEntity &ship);
    int GetArea();
};

#endif
