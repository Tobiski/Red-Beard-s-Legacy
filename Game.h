#ifndef _GAME_H_
#define _GAME_H_

#define MAXFPS 80

#include <vector>

#include <SFML\Graphics.hpp>

class Cannonball;
class Ship;
class Enemy;

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event event;
	bool running;
	Ship *ship;
	std::vector<Cannonball*> cannonballs;
	std::vector<Enemy*> enemies;
	int cannonballsOnScreen;
	sf::Font scoreFont;
	sf::Image pirateImage;
	sf::Sprite pirateSprite;
	int spawnCooldown;

public:
	Game();
	~Game();
	void Init();
	void GameLoop();
	void HandleInput();
	void Update();
	void Render();

};

#endif