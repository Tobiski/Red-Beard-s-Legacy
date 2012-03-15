#include <iostream>
#include "Enemy.h"
#include "Cannonball.h"
#include "Misc.h"

Enemy::Enemy()
{
	forceTurn = false;
	image.LoadFromFile("images/ship.png");
	image.SetSmooth(false);
	sprite.SetImage(image);
	sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
	if(rand()%2 == 0)
	{
		posx = -50;
		rotationAngle = 90;
	}
	else
	{
		posx = WIN_WIDTH + 50;
		rotationAngle = 270;
	}
	posy = rand()%(WIN_HEIGHT - 200 ) + 100;
	sprite.SetRotation(rotationAngle);
	sprite.SetPosition(posx, posy);
	turnTime = 400;
	turnDirection = 2;
	health = 3;
	shootTime.Reset();
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	speedx = sin(rotationAngle*3.14159265/180);
	speedy = cos(rotationAngle*3.14159265/180);

	/* If ship has collided then we turn it to another direction for 1 sec */
	if(cTurnTime.GetElapsedTime() < 1 && forceTurn == true)
	{
		if(forceDirection == LEFT)
			rotationAngle--;
		else
			rotationAngle++;
	}
	else 
	{
		forceTurn = false;

		Turn();
	}

	if(posx + speedx > 100 && posx+ speedx < WIN_WIDTH - 100 || turnTime > 200)
	{
		posx = posx + speedx;
	}

	if(posy+ speedy*-1 > 100 && posy+ speedy*-1 < WIN_HEIGHT - 100)
	{
		posy = posy + speedy*-1;
	}

	sprite.SetRotation(rotationAngle*-1);
	sprite.SetPosition(posx, posy);
	if(turnTime > 0)
	{
		turnTime--;
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.Draw(sprite);

	sf::Color hbBackColor(255, 0, 0, 255);
	sf::Shape healthBackbar = sf::Shape::Rectangle(posx-30,posy-60,posx+30,posy-55, hbBackColor);
	window.Draw(healthBackbar);

	sf::Color hbColor(0, 255, 0, 255);
	sf::Shape healthbar = sf::Shape::Rectangle(posx-30,posy-60,posx-30+(20*health),posy-55, hbColor);
	window.Draw(healthbar);
}

void Enemy::Turn()
{
	if(turnTime == 0)
	{
		turnTime = 200;
		if(posx < 100 || posx > WIN_WIDTH - 10 || posy < 100 || posy > WIN_HEIGHT - 100)
		{
			turnDirection = rand()%3;
		}
		else
		{
			turnDirection = rand()%3;
		}
	}

	if(turnDirection == RIGHT)
	{
		rotationAngle++;
	}
	else if(turnDirection == LEFT)
	{
		rotationAngle--;
	}
	else
	{
		rotationAngle = rotationAngle;
	}
}

void Enemy::Fire(std::vector<Cannonball*> &cannonballs)
{
	if(shootTime.GetElapsedTime() > 1)
	{
		if(rand()%3 == 0)
		{
			cannonballs.push_back(new Cannonball(posx, posy, (rotationAngle+90), ENEMY));
		}
		
		shootTime.Reset();
	}
}

void Enemy::ForceTurn(int dir) 
{
	forceTurn = true;
	cTurnTime.Reset();
	originalRotation = sprite.GetRotation();
	forceDirection = dir;
}