#ifndef MONSTER_H
#define MONSTER_H

#include "Drawable.h"

enum MonsterType { OCTOPUSSY, SNAKE, JELLYFISH };
enum Acceleration { DECREASE, INCREASE };

class Monster : public Drawable
{
    public:
        Monster();
        virtual ~Monster();
        void Update(float playerX, float playerY);
        void Update() {}
    protected:
    private:
        MonsterType monsterType;
        Acceleration accelState;
};

#endif // MONSTER_H
