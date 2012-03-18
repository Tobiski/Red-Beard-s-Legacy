#ifndef SWORDMAN_H
#define SWORDMAN_H

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define MIDDLE 4

#include "../include/Drawable.h"

class SwordMan : public Drawable
{
    public:
        SwordMan();
        virtual ~SwordMan();

        void Update() {}
        void Strike(const int direction) {}
        void Defence(const int direction) {}
        void LoseEnergy() {}
        void Move(const int direction) {}
    private:
        sf::Image image;
        sf::Sprite sprite;
};

#endif // SWORDMAN_H
