/*
 *  Object from this class should not see nor call
 *  any other methods than Fight()
 *
 *  Class creates a new 'game' inside our game where is
 *  two swordsman fighting eachother.  Fight then return
 *  the winner of the match.
 *
 */

#ifndef SWORDFIGHT_H
#define SWORDFIGHT_H

#include <SFML/Graphics.hpp>
#include "../include/SwordMan.h"
#define COMPUTER 0
#define PLAYER 1

enum GameState { PAUSE, PLAY };

class SwordFight
{
    public:
        SwordFight(sf::RenderWindow* window);
        virtual ~SwordFight();
        bool Fight(); // returns sword winner

    private:
        void GameLoop();
        void LoopKeys();
        void Update();
        void draw();
        void Lose();
        void Win();

        sf::RenderWindow* window;
        sf::Event event;

        GameState gameState;

        sf::Image bgImage;
        sf::Sprite bgSprite;

        SwordMan* player;
        SwordMan* computer;

        float deltaX;
        int playerChoise;
        int aiChoise;

        bool winner;
        bool running;

        // Keyboard flags
        bool left;
        bool right;
        bool up;
        bool down;
        bool space;
        bool enter;
        bool escape;
};

#endif // SWORDFIGHT_H
