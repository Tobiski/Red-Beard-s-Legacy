#ifndef _CANNONBALL_H_
#define _CANNONBALL_H_

#include <SFML/Graphics.hpp>

class ShipEntity;
class Enemy;

class Cannonball
{
private:
    int id;
    float posx;
    float posy;
    float direction;
    sf::Clock spawnTime;
    sf::Image image;
    sf::Sprite sprite;
public:
    Cannonball(float posx, float posy, float direction, int id);
    ~Cannonball();
    void Update();
    void Draw(sf::RenderWindow &window);
    float GetXpos()
    {
        return posx;
    }
    float GetYpos()
    {
        return posy;
    }
    bool CheckCollision(ShipEntity &enemy);
    float GetTime()
    {
        return spawnTime.GetElapsedTime();
    }
    int GetId()
    {
        return id;
    }
    int GetArea();
};

#endif
