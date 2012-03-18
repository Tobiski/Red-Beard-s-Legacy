#ifndef MONSTER_H
#define MONSTER_H

#include "Drawable.h"

enum MonsterType { OCTOPUSSY, SNAKE, JELLYFISH };

class Monster : public Drawable
{
    public:
        Monster();
        virtual ~Monster();
        void Update();
    protected:
    private:
        MonsterType monsterType;
};

#endif // MONSTER_H
