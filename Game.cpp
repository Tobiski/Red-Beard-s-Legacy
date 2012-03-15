#include <iostream>

#include "Game.h"
#include "Misc.h"
#include "Ship.h"
#include "Cannonball.h"
#include "Enemy.h"

Game::Game()
{
	running = true;
	srand(time(NULL));
	Init();
}

Game::~Game()
{
	delete ship;
	window->Close();
}

void Game::Init()
{
	scoreFont.LoadFromFile("Treamd.ttf");

	pirateImage.LoadFromFile("images/pirate_face.png");
	pirateImage.SetSmooth(false);
	pirateSprite.SetImage(pirateImage);
	pirateSprite.SetPosition(WIN_WIDTH - 160, 10);

	spawnCooldown = 0;
	running = true;
	window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT, WIN_BPP), "Untitled Game");
	window->SetFramerateLimit(MAXFPS);
	ship = new Ship("images/ship.png", 100, 100);
	cannonballsOnScreen = 0;
	GameLoop();
}

void Game::GameLoop()
{
	while(running)
	{
		HandleInput();
		Update();
		Render();
	}
}

void Game::HandleInput()
{
	while(window->GetEvent(event))
	{
		if(event.Type == sf::Event::Closed)
		{
			window->Close();
		}

		if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::S)
		{
			enemies.push_back(new Enemy());
		}
	}

	if(window->GetInput().IsKeyDown(sf::Key::Up))
	{
		ship->Accel(0);
	}
	else
	{
		if(ship->GetAccel() > 0)
		{
			ship->Accel(1);
		}
	}
	if(window->GetInput().IsKeyDown(sf::Key::Left)) ship->Turn(LEFT);
	if(window->GetInput().IsKeyDown(sf::Key::Right)) ship->Turn(RIGHT);
	if(window->GetInput().IsKeyDown(sf::Key::Space)) ship->Fire(cannonballs);
}

void Game::Update()
{
	if(enemies.size() < 5 && spawnCooldown == 0)
	{
		enemies.push_back(new Enemy());
		spawnCooldown = 200;
	}
	else
	{
		if(spawnCooldown > 0)
		{
			spawnCooldown--;
		}
	}

	ship->Update();

	if(ship->GetHeatlth() == 0)
	{
		window->Close();
	}

	/* Update positions */
	for(int i = 0; i < cannonballs.size(); i++)
	{
		cannonballs[i]->Update();
	}

	for(int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update();
		enemies[i]->Fire(cannonballs);
	}

	/* START CHECKING COLLISION */
	for(int i = 0; i < enemies.size(); i++)
	{
		for(int j = 0; j < enemies.size(); j++)
		{
			if(enemies[i]->GetArea() != enemies[j]->GetArea())
			{
				continue;
			}
			if(i != j)	// check that ships don't collide with themselfs
				if(enemies[i]->CheckCollision(*enemies[j]))
				{
					enemies[i]->ForceTurn(LEFT);
					enemies[j]->ForceTurn(RIGHT);
				}
		}
	}

	/* Check cannonball live against ships */
	for(int i = 0; i < cannonballs.size(); i++)
	{
		if(cannonballs[i]->GetTime() > 0.5)
		{
			if(cannonballs.size() > 0)
			{
				cannonballs.erase(cannonballs.begin() + i);
			}
		}
		else
		{
			cannonballs[i]->Update();

			for(int j = 0; j < enemies.size() ; j++)
			{

				if(cannonballs[i]->GetArea() != enemies[j]->GetArea())
				{
					continue;
				}

				if(cannonballs[i]->GetId() == ENEMY)
				{
					if(cannonballs[i]->CheckCollision(*ship))
					{
						ship->GetHit();
						cannonballs.erase(cannonballs.begin()+i);
						break;
					}
				}

				if(cannonballs[i]->CheckCollision(*enemies[j]))
				{
					if(cannonballs[i]->GetId() != 1)
					{
						if(enemies[j]->GetHeatlth() > 1)
						{
							enemies[j]->GetHit();
							cannonballs.erase(cannonballs.begin()+i);
							ship->AddScore();
							break;
						}
						else
						{
 							enemies.erase(enemies.begin()+j);
							cannonballs.erase(cannonballs.begin()+i);
							ship->AddScore();
							break;
						}
					}
				}
			} // end for-enemies
		}
	} // end for-cannonballs


}

void Game::Render()
{
	window->Clear(sf::Color(0, 90, 255));
	ship->Draw(*window);
	for(int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Draw(*window);
	}
	for(int i = 0; i < cannonballs.size(); i++)
	{
		cannonballs[i]->Draw(*window);
	}

	sf::Color healthColor(0, 255, 0, 200);
	sf::Color transparent(0, 0, 0, 0);
	sf::Color borderColor(0, 0, 0, 255);
	sf::Shape healthBar = sf::Shape::Rectangle(WIN_WIDTH - 120, 20, WIN_WIDTH - 120 + (ship->GetHeatlth()*20), 40, healthColor);
	sf::Shape borders = sf::Shape::Rectangle(WIN_WIDTH - 120, 20, WIN_WIDTH - 20, 40, transparent, 2, borderColor);
	window->Draw(healthBar);
	window->Draw(borders);

	sf::String scoreText(ship->GetScore(), scoreFont, 24);
	scoreText.SetColor(sf::Color(0, 0, 0, 255));
	scoreText.SetPosition(WIN_WIDTH - 120, 40);
	window->Draw(scoreText);

	window->Draw(pirateSprite);

	window->Display();
}
