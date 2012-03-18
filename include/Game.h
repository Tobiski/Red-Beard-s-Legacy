#ifndef _GAME_H_
#define _GAME_H_

#define MAXFPS 80

#include <vector>

#include <SFML/Graphics.hpp>

class Cannonball;
class Ship;
class Enemy;
class Animation;
class Monster;

class Game
{
private:
    sf::RenderWindow* window;
    sf::Event event;
    bool running;
    Ship *ship;
    std::vector<Animation*> animations;
    std::vector<Cannonball*> cannonballs;
    std::vector<Enemy*> enemies;
    sf::Font scoreFont;
    sf::Image gameOverImage;
    sf::Sprite gameOverSprite;
    sf::Image menuImage;
    sf::Sprite menuSprite;
    sf::Image skullImage;
    sf::Sprite skullSprite;
    sf::Image pauseSkullImage;
    sf::Sprite pauseSkullSprite;
    sf::Image pirateImage;
    sf::Sprite pirateSprite;
    sf::Sprite seaSprite;
    sf::Image seaImage;
    int spawnCooldown;
    enum MENUSELECT {START, QUIT};
    MENUSELECT menuSelect;
    enum PAUSESELECT {RESUME, MENU};
    PAUSESELECT pauseSelect;
    enum GAMESTATE {MAINMENU, PLAYING, PAUSED, GAMEOVER};
    GAMESTATE gameState;
    std::clock_t monsterTimer;
    double delta;
    Monster *monster;

public:
    Game();
    ~Game();
    void Init();
    void GameOver();
    void GameLoop();
    void HandleInput();
    void Update();
    void Render();

};

#endif
