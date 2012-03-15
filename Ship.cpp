#include <iostream>
#include "Misc.h"
#include "Ship.h"
#include "Cannonball.h"

Ship::Ship(std::string imageDir, float posx, float posy)
{
	image.LoadFromFile(imageDir);
	image.SetSmooth(false);
	sprite.SetImage(image);
	this->posx = posx;
	this->posy = posy;
	sprite.SetPosition(this->posx, this->posy);
	accel = 0;
	rotationAngle = 0;
	sprite.SetCenter(sprite.GetSize().x / 2, sprite.GetSize().y / 2);
	speedx = 0;
	speedy = 0;
	cooldown = 0;
	score = 0;
	health = 5;
}

Ship::~Ship()
{
}

void Ship::Draw(sf::RenderWindow& window)
{
	window.Draw(sprite);
}

void Ship::Accel(int dir)
{
	switch(dir)
	{
	case 0:
		if(accel < 1)
		{
			accel = accel + 0.01;
		}
		else
		{
			accel = 1;
		}
		break;
	case 1:
		if(accel > 0.05)
		{
			accel = accel - 0.005;
		}
		else
		{
			accel = 0.05;
		}
		break;
	}
}

void Ship::Turn(int dir)
{
	switch(dir)
	{
	case 0:
		rotationAngle++;
		if(rotationAngle > 360)
		{
			rotationAngle = 0;
		}
		break;
	case 1:
		rotationAngle--;
		if(rotationAngle < 0)
		{
			rotationAngle = 360;
		}
	}
}

void Ship::Update()
{
	speedx = accel * sin(rotationAngle*3.14159265/180);
	speedy = accel * cos(rotationAngle*3.14159265/180);

	if(posx+ speedx > 0 && posx+ speedx < WIN_WIDTH)
	{
		posx = posx + speedx;
	}
	else
	{
		posx = posx;
	}
	if(posy+ speedy*-1 > 0 && posy+ speedy*-1 < WIN_HEIGHT)
	{
		posy = posy + speedy*-1;
	}
	else
	{
		posy = posy;
	}

	if(cooldown > 0)
	{
		cooldown--;
	}

	sprite.SetRotation(rotationAngle*-1);
	sprite.SetPosition(posx, posy);
}

void Ship::Fire(std::vector<Cannonball*> &cannonballs)
{	
	if(cooldown == 0)
	{
		cooldown = 80;
		cannonballs.push_back(new Cannonball(posx, posy, (rotationAngle+90), PLAYER));
	}
}

std::string Ship::GetScore()
{
	std::string scoreString = "Score: ";
	std::string addString;
	char points[11];
	itoa(score, points, 10);
	addString.assign(points);
	scoreString += addString;
	
	return scoreString;
}