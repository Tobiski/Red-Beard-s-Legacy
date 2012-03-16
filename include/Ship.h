#ifndef _SHIP_H_
#define _SHIP_H_

#include "ShipEntity.h"



class Cannonball;

class Ship : public ShipEntity
{
private:
    int cooldown;
    int score;
    int shipsHit;
    int cannonballsShot;
    float accuracy;
public:
    Ship();
    Ship(std::string imageDir, float posx, float posy);
    ~Ship();
    void Update();
    void Draw(sf::RenderWindow& window);
    void Accel(int dir);
    void Turn(int dir);
    void Fire(std::vector<Cannonball*> &cannonballs);
    void AddScore()
    {
        score += 10;
    }
    void AddHit()
    {
        shipsHit++;
    }
    std::string GetInfo();
    std::string GetScore();
};

#endif
