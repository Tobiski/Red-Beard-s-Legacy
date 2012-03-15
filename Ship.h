#ifndef _SHIP_H_
#define _SHIP_H_

#include "ShipEntity.h"

class Cannonball;

class Ship : public ShipEntity
{
private:
	int cooldown;
	int score;
	int shipsDestroyed;
	int cannonballsShot;
public:
	Ship();
	Ship(std::string imageDir, float posx, float posy);
	~Ship();
	void Update();
	void Draw(sf::RenderWindow& window);
	void Accel(int dir);
	void Turn(int dir);
	void Fire(std::vector<Cannonball*> &cannonballs);
	void AddScore(){score += 10;}
	void AddShipsDestroyed(){shipsDestroyed++;}
	std::string GetInfo();
	std::string GetScore();
};

#endif
