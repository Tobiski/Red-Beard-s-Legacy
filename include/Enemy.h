#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "ShipEntity.h"

class Enemy : public ShipEntity
{
private:
    int turnTime;
    float turnDirection;
    int counter;
    sf::Clock shootTime;
    sf::Clock cTurnTime; // forces turn to specific time
    bool forceTurn;
    int lastDirection;
    int forceDirection;
    int originalRotation;
    bool intruder;
public:
    Enemy();
    ~Enemy();
    void Update();
    void Draw(sf::RenderWindow& window);
    void Turn();
    void Fire(std::vector<Cannonball*> &cannonballs);
    void ForceTurn(int dir); // ship has collided with another shipol

    bool GetIntruder() { return intruder; }
    void SetIntruder(bool intr) { intruder = intr; }
};

#endif
