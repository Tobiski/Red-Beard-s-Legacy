#ifndef MONSTER_H
#define MONSTER_H

#include "Drawable.h"

enum MonsterType { OCTOPUSSY, SNAKE, JELLYFISH };
enum Acceleration { DECREASE, INCREASE };

class ShipEntity;
class Animation;

class Monster : public Drawable
{
    public:
        Monster();
        virtual ~Monster();
        void Update(float playerX, float playerY);
        void Update() {}
        void DrawSpawningAnimation (sf::RenderWindow &ewindow);
        bool CheckCollision(ShipEntity &ship);
        bool IsSpawning() { return spawning; }
    protected:
    private:
        MonsterType monsterType;
        Acceleration accelState;
        bool spawning;
        Animation *spawnAnimation;
};

#endif // MONSTER_H
