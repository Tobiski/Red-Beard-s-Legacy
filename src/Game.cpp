#include <iostream>

#include "../include/Game.h"
#include "../include/Misc.h"
#include "../include/Ship.h"
#include "../include/Cannonball.h"
#include "../include/Enemy.h"

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

    menuImage.LoadFromFile("images/menu.png");
    menuSprite.SetImage(menuImage);
    menuSprite.SetPosition(0,0);

    gameOverImage.LoadFromFile("images/gameover.png");
    gameOverSprite.SetImage(gameOverImage);
    gameOverSprite.SetPosition(0, 0);

    skullImage.LoadFromFile("images/skull.png");
    skullImage.SetSmooth(false);
    skullSprite.SetImage(skullImage);

    pirateImage.LoadFromFile("images/pirate_face.png");
    pirateImage.SetSmooth(false);
    pirateSprite.SetImage(pirateImage);
    pirateSprite.SetPosition(WIN_WIDTH - 160, 10);

    gameState = MAINMENU;
    menuSelect = START;

    spawnCooldown = 0;
    running = true;
    window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT, WIN_BPP), "Red Beard's Legacy");
    window->SetFramerateLimit(MAXFPS);

    ship = new Ship("images/ship.png", 100, 100);

    GameLoop();
}

void Game::GameOver()
{
    cannonballs.clear();
    enemies.clear();
    gameState = GAMEOVER;

    GameLoop();
}

void Game::GameLoop()
{
    while(running)
    {
        if(gameState == MAINMENU || gameState == GAMEOVER)
        {
            /* Display mainmenu or Game Over -screen */
            HandleInput();
            Render();
        }
        else if(gameState == PLAYING)
        {
            /* Display game */
            HandleInput();
            Update();
            Render();
        }
        else if(gameState == PAUSED)
        {
            /* Display pause menu*/
            HandleInput();
        }
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

        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)
        {
            if(gameState == PLAYING)
            {
                gameState = PAUSED;
            }
            else if(gameState == PAUSED)
            {
                gameState = PLAYING;
            }
        }

        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Down && gameState == MAINMENU)
        {
            if(menuSelect == START)
                menuSelect = QUIT;
        }

        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Up && gameState == MAINMENU)
        {
            if(menuSelect == QUIT)
                menuSelect = START;
        }

        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Return)
        {
            if(gameState == MAINMENU && menuSelect == QUIT)
            {
                window->Close();
            }
            else if(gameState == MAINMENU && menuSelect == START)
            {
                gameState = PLAYING;
            }
            if(gameState == GAMEOVER)
            {
                gameState = MAINMENU;
                ship = new Ship("images/ship.png", 100, 100);
            }
        }

        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::S && gameState == PLAYING)
        {
            enemies.push_back(new Enemy());
        }
    }

    if(gameState == PLAYING)
    {
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

    if(ship->GetHealth() == 0)
    {
        GameOver();
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
                    /* If cannonball belongs to player, check collision against enemy ships */
                    if(cannonballs[i]->GetId() != ENEMY)
                    {
                        if(enemies[j]->GetHealth() > 1)
                        {
                            enemies[j]->GetHit();
                            cannonballs.erase(cannonballs.begin()+i);
                            ship->AddHit();
                            ship->AddScore();
                            break;
                        }
                        else
                        {
                            enemies.erase(enemies.begin()+j);
                            cannonballs.erase(cannonballs.begin()+i);
                            ship->AddHit();
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
    if(gameState == MAINMENU)
    {
        window->Draw(menuSprite);
        if(menuSelect == START)
        {
            skullSprite.SetPosition(340, 290);
        }
        else if(menuSelect == QUIT)
        {
            skullSprite.SetPosition(340, 400);
        }
        window->Draw(skullSprite);
    }
    else if(gameState == PLAYING)
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
        sf::Shape healthBar = sf::Shape::Rectangle(WIN_WIDTH - 120, 20, WIN_WIDTH - 120 + (ship->GetHealth()*20), 40, healthColor);
        sf::Shape borders = sf::Shape::Rectangle(WIN_WIDTH - 120, 20, WIN_WIDTH - 20, 40, transparent, 2, borderColor);
        window->Draw(healthBar);
        window->Draw(borders);

        sf::String scoreText(ship->GetScore(), scoreFont, 24);
        scoreText.SetColor(sf::Color(0, 0, 0, 255));
        scoreText.SetPosition(WIN_WIDTH - 120, 40);
        window->Draw(scoreText);

        window->Draw(pirateSprite);
    }
    else if(gameState == PAUSED)
    {
        sf::String pausedText("PAUSED", scoreFont, 42);
        pausedText.SetColor(sf::Color(0, 0, 0, 200));
        pausedText.SetCenter(pausedText.GetSize(), pausedText.GetSize());
        pausedText.SetPosition(WIN_WIDTH/2, WIN_HEIGHT/2);
        window->Draw(pausedText);
    }
    else if(gameState == GAMEOVER)
    {
        window->Draw(gameOverSprite);

        sf::String infoText(ship->GetInfo(), scoreFont, 32);
        infoText.SetCenter(infoText.GetSize(), infoText.GetSize());
        infoText.SetColor(sf::Color(0, 0, 0, 255));
        infoText.SetPosition(WIN_WIDTH/2 - 100, WIN_HEIGHT/2 + 100);
        window->Draw(infoText);
    }

    window->Display();
}
