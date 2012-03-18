#ifndef _GAME_H_
#define _GAME_H_

#define MAXFPS 80

#include <vector>

#include <SFML/Graphics.hpp>

enum MENUSELECT { START, QUIT };
enum PAUSESELECT { RESUME, MENU };
enum HARBORSELECT { ENTER_MARKET, EXIT_HARBOR };
enum MARKETSELECT { REPAIR, UPGRADE, EXIT_MARKET };
enum GAMESTATE { MAINMENU, PLAYING, PAUSED, HARBOR, MARKET, GAMEOVER };

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
    MENUSELECT menuSelect;
    PAUSESELECT pauseSelect;
    GAMESTATE gameState;
    HARBORSELECT harborSelect;
    MARKETSELECT marketSelect;

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
