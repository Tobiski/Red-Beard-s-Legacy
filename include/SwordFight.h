#ifndef SWORDFIGHT_H
#define SWORDFIGHT_H

#include <SFML/Graphics.hpp>

class SwordFight
{
    public:
        SwordFight();
        virtual ~SwordFight();
    protected:
    private:
        sf::RenderWindow* window;
        sf::Event event;
        bool running;

        sf::Image bgImage;
        sf::Sprite bgSprite;

};

#endif // SWORDFIGHT_H
