#ifndef _SHIP_H_
#define _SHIP_H_

#include "ShipEntity.h"



class Cannonball;

class Ship : public ShipEntity
{
private:
    int cooldown;
    int score;
    int gold;
    int cannonLevel;
    int shipsHit;
    int cannonballsShot;
    float accuracy;
public:
    Ship();
    Ship(std::string imageDir, float posx, float posy);
    ~Ship();
    void Update();
    void Accel(int dir);
    void Turn(int dir);
    void Fire(std::vector<Cannonball*> &cannonballs);
    bool RemoveGold(int amount);
    void UpgradeCannons() { cannonLevel++; };
    int GetGold() { return gold; }
    int GetCannonLevel() { return cannonLevel; }
    void AddScore()
    {
        score += 10;
    }
    void AddHit()
    {
        shipsHit++;
    }
    void Repair()
    {
        health++;
    }
    void AddGold(int amount)
    {
        gold += amount;
    }
    std::string GetInfo();
    std::string GetScore();
    std::string GetGoldString();
};

#endif
