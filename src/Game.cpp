#include <iostream>
#include <time.h>

#include "../include/Game.h"
#include "../include/Misc.h"
#include "../include/Ship.h"
#include "../include/Cannonball.h"
#include "../include/Enemy.h"
#include "../include/Animation.h"
#include "../include/Monster.h"
#include "../include/TextBox.h"
#include "../include/SwordFight.h"
#include "../include/TopScore.h"
#include "../include/Collision.h"

Game::Game()
{
    TopScore top;
    int r = top.addNewScore("dotdeb",1,1.0f,1.0f);
    std::cout << r << std::endl;
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
    textBox = NULL;
    monster = NULL;
    monsterTimer = std::clock();
    scoreFont.LoadFromFile("Treamd.ttf");

    menuImage.LoadFromFile("images/menu.png");
    menuSprite.SetImage(menuImage);
    menuSprite.SetPosition(0,0);

    pauseMenuImage.LoadFromFile("images/pauseMenu.png");
    pauseMenuSprite.SetImage(pauseMenuImage);
    pauseMenuSprite.SetPosition(WIN_WIDTH / 2 - (pauseMenuSprite.GetSize().x / 2), WIN_HEIGHT / 2 - (pauseMenuSprite.GetSize().y / 2));

    seaImage.LoadFromFile("images/sea.png");
    seaSprite.SetImage(seaImage);
    seaSprite.SetPosition(0,0);

    gameOverImage.LoadFromFile("images/gameover.png");
    gameOverSprite.SetImage(gameOverImage);
    gameOverSprite.SetPosition(0, 0);

    skullImage.LoadFromFile("images/skull.png");
    skullImage.SetSmooth(false);
    skullSprite.SetImage(skullImage);

    pauseSkullImage.LoadFromFile("images/pauseskull.png");
    pauseSkullImage.SetSmooth(false);
    pauseSkullSprite.SetImage(pauseSkullImage);

    pirateImage.LoadFromFile("images/pirate_face.png");
    pirateImage.SetSmooth(false);
    pirateSprite.SetImage(pirateImage);
    pirateSprite.SetPosition(WIN_WIDTH - 160, 10);

    harborImage.LoadFromFile("images/harbor.png");
    harborImage.SetSmooth(false);
    harborSprite.SetImage(harborImage);
    harborSprite.SetPosition(100, 0);

    gameState = MAINMENU;
    menuSelect = START;
    harborSelect = ENTER_MARKET;
    marketSelect = REPAIR;

    spawnCooldown = 0;
    running = true;
    window = new sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT, WIN_BPP), "Red Beard's Legacy");
    window->SetFramerateLimit(MAXFPS);

    ship = new Ship("images/playerShip.png", 150, 100);

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
        else if(gameState == PAUSED || gameState == HARBOR || gameState == MARKET)
        {
            /* Display pause menu, Harbor menu or Market menu*/
            HandleInput();
            Render();
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
                pauseSelect = RESUME;
            }
            else if(gameState == PAUSED)
            {
                gameState = PLAYING;
            }
        }

        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Down)
        {
            if(gameState == MAINMENU)
            {
                if(menuSelect == START)
                    menuSelect = QUIT;
            }
            else if(gameState == PAUSED)
            {
                if(pauseSelect == RESUME)
                    pauseSelect = MENU;
            }
            else if(gameState == HARBOR)
            {
                if(harborSelect == ENTER_MARKET)
                    harborSelect = EXIT_HARBOR;
            }
            else if(gameState == MARKET)
            {
                if(marketSelect == REPAIR)
                    marketSelect = UPGRADE;
                else if(marketSelect == UPGRADE)
                    marketSelect = EXIT_MARKET;
            }
        }

        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Up)
        {
            if(gameState == MAINMENU)
            {
                if(menuSelect == QUIT)
                    menuSelect = START;
            }
            else if(gameState == PAUSED)
            {
                if(pauseSelect == MENU)
                    pauseSelect = RESUME;
            }
            else if(gameState == HARBOR)
            {
                if(harborSelect == EXIT_HARBOR)
                    harborSelect = ENTER_MARKET;
            }
            else if(gameState == MARKET)
            {
                if(marketSelect == UPGRADE)
                    marketSelect = REPAIR;
                else if(marketSelect == EXIT_MARKET)
                    marketSelect = UPGRADE;
            }
        }

        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Return)
        {
            if(gameState == MAINMENU && menuSelect == QUIT)
                window->Close();
            else if(gameState == MAINMENU && menuSelect == START)
                gameState = PLAYING;
            else if(gameState == PAUSED && pauseSelect == RESUME)
                gameState = PLAYING;
            else if(gameState == PAUSED && pauseSelect == MENU)
            {
                gameState = MAINMENU;
                cannonballs.clear();
                enemies.clear();
                ship = new Ship("images/playerShip.png", 100, 100);
            }
            else if(gameState == GAMEOVER)
            {
                gameState = MAINMENU;
                ship = new Ship("images/playerShip.png", 100, 100);
            }
            else if(gameState == HARBOR && harborSelect == ENTER_MARKET)
                gameState = MARKET;
            else if(gameState == HARBOR && harborSelect == EXIT_HARBOR)
            {
                gameState = PLAYING;
                harborSelect = ENTER_MARKET;
                ship->SetRotation(90);
                ship->SetposX(150);
                ship->SetposY(100);
            }
            else if(gameState == MARKET && marketSelect == REPAIR)
            {
                if(ship->GetHealth() < 5 && ship->GetGold() >= 100)
                {
                    ship->Repair();
                    ship->RemoveGold(100);
                    textBox = new TextBox(0, 0, "You repaired the ship for 100 golds.");
                }
                else if(ship->GetGold() < 100)
                    textBox = new TextBox(0, 0, "You don't have enough gold to repair the ship.");
                else if(ship->GetHealth() == 5)
                    textBox = new TextBox(0, 0, "The ship is already fully repaired.");
            }
            else if(gameState == MARKET && marketSelect == UPGRADE)
                if(ship->GetGold() >= 1000)
                {
                    if(ship->GetCannonLevel() < MAX_CANNON_LEVEL)
                    {
                        ship->UpgradeCannons();
                        ship->RemoveGold(1000);
                        textBox = new TextBox(0, 0, "You upgraded the cannons for 1000 golds.");
                    }
                    else
                    {
                        ship->UpgradeCannons();
                        textBox = new TextBox(0, 0, "Your cannons are already fully upgraded.");
                    }
                }
                else
                    textBox = new TextBox(0, 0, "You don't have enough gold\nto upgrade the cannons.");
            else if(gameState == MARKET && marketSelect == EXIT_MARKET)
            {
                gameState = HARBOR;
                marketSelect = REPAIR;
            }
        }

        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::S && gameState == PLAYING)
        {
            enemies.push_back(new Enemy());
        }
        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::M && gameState == PLAYING)
        {
            monster = new Monster();
            textBox = new TextBox(0, 0, "A horrible monster has risen from the sea!");
        }
        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::W && gameState == PLAYING)
        {
            gameState = HARBOR;
        }
        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::A && gameState == PLAYING)
        {
            animations.push_back(new Animation(100, 100, 0, "images/monsterSpawnAnimation.png", 10));
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
    /* Check if the message have been displayed for 2 seconds*/
    if(textBox != NULL)
    {
        if(textBox->GetTime() > 2)
        {
            delete textBox;
            textBox = NULL;
        }
    }

    /* Check if we can create a monster */
    delta = (std::clock() - monsterTimer) / (double)CLOCKS_PER_SEC;
    if(delta > 10 && monster == NULL)
    {
        if(rand()%4 == 0)
        {
            monster = new Monster();
            textBox = new TextBox(0, 0, "A horrible monster has risen from the sea!");
        }
    }

    if(monster != NULL)
    {
        monster->Update(ship->GetXpos(), ship->GetYpos());
    }

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

    if(ship->GetHealth() <= 0)
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

    /* Update animations */
    for(int i = 0; i < animations.size(); i++)
    {
        animations[i]->Update();
    }

    for(int i = 0; i < animations.size(); i++)
    {
        if(animations[i]->GetCurrentFrame() == animations[i]->GetMaxFrames())
            animations.erase(animations.begin() + i);
    }

    /* Start checking collision */

    /* Check if the player enters the barbor */
    if(Collision::PixelPerfectTest(ship->GetSprite(), harborSprite))
        gameState = HARBOR;

    /* Check if enemies collide against each other */
    for(int i = 0; i < enemies.size(); i++)
    {
        for(int j = 0; j < enemies.size(); j++)
        {
            if(enemies[i]->GetArea() != enemies[j]->GetArea())
            {
                continue;
            }
            if(i != j)// check that ships don't collide with themselfs
            {
                if(Collision::PixelPerfectTest(enemies[i]->GetSprite(), enemies[j]->GetSprite()))
                //if(enemies[i]->CheckCollision(*enemies[j]))
                {
                    enemies[i]->ForceTurn(LEFT);
                    enemies[j]->ForceTurn(RIGHT);
                }
            }
        }
    }

    /* Check monster collision against player's ship */
    if(monster != NULL)
    {
        if(Collision::PixelPerfectTest(ship->GetSprite(), monster->GetSprite()))
        {
            ship->GetHit(2);
            delete monster;
            monster = NULL;
            monsterTimer = std::clock();
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

            /* Check cannonball collision against monster */
            if(monster != NULL)
            {
                if(cannonballs[i]->CheckCollision(*monster))
                {
                    ship->AddScore();
                    cannonballs.erase(cannonballs.begin()+i);
                    monster->GetHit(ship->GetCannonLevel());
                    if(monster->GetHealth() <= 0)
                    {
                        delete monster;
                        monster = NULL;
                        monsterTimer = std::clock();
                    }
                    break;
                }
            }

            for(int j = 0; j < enemies.size() ; j++)
            {
                if(cannonballs[i]->GetArea() != enemies[j]->GetArea())
                {
                    continue;
                }

                if(cannonballs[i]->GetId() == ENEMY)
                {
                    if(Collision::PixelPerfectTest(ship->GetSprite(), cannonballs[i]->GetSprite()))
                    {
                        ship->GetHit(1);
                        cannonballs.erase(cannonballs.begin()+i);
                        break;
                    }
                }

                if(Collision::PixelPerfectTest(cannonballs[i]->GetSprite(), enemies[j]->GetSprite()))
                {
                    /* If cannonball belongs to player, check collision against enemy ships */
                    if(cannonballs[i]->GetId() != ENEMY)
                    {
                        if(enemies[j]->GetHealth() > ship->GetCannonLevel())
                        {
                            enemies[j]->GetHit(ship->GetCannonLevel());
                            cannonballs.erase(cannonballs.begin()+i);
                            ship->AddHit();
                            ship->AddScore();
                            break;
                        }
                        else
                        {
                            animations.push_back(new Animation(enemies[j]->GetXpos(), enemies[j]->GetYpos(), enemies[j]->GetRotation(), "images/shipAnimation.png", 10));
                            enemies.erase(enemies.begin()+j);
                            cannonballs.erase(cannonballs.begin()+i);
                            ship->AddHit();
                            ship->AddScore();
                            ship->AddGold(10);
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
        window->Draw(seaSprite);

        window->Draw(harborSprite);

        if(monster != NULL && monster->IsSpawning() == false)
        {
            monster->Draw(*window);
        }
        else if(monster != NULL && monster->IsSpawning() == true)
        {
            monster->DrawSpawningAnimation(*window);
        }

        ship->Draw(*window);
        for(int i = 0; i < enemies.size(); i++)
        {
            enemies[i]->Draw(*window);
        }

        for(int i = 0; i < cannonballs.size(); i++)
        {
            cannonballs[i]->Draw(*window);
        }

        for(int i = 0; i < animations.size(); i++)
        {
            animations[i]->Draw(*window);
        }

        sf::Color healthColor(0, 255, 0, 200);
        sf::Color transparent(0, 0, 0, 0);
        sf::Color borderColor(0, 0, 0, 255);
        sf::Shape healthBar = sf::Shape::Rectangle(WIN_WIDTH - 120, 20, WIN_WIDTH - 120 + (ship->GetHealth()*20), 40, healthColor);
        sf::Shape borders = sf::Shape::Rectangle(WIN_WIDTH - 120, 20, WIN_WIDTH - 20, 40, transparent, 2, borderColor);
        window->Draw(healthBar);
        window->Draw(borders);

        sf::String goldText(ship->GetGoldString(), scoreFont, 24);
        goldText.SetColor(sf::Color(255, 255, 0, 255));
        goldText.SetPosition(WIN_WIDTH - 120, 40);
        window->Draw(goldText);

        window->Draw(pirateSprite);
    }

    else if(gameState == HARBOR)
    {
        window->Clear();
        window->Draw(seaSprite);
        window->Draw(pauseMenuSprite);

        sf::String harborText("HARBOR", scoreFont, 42);
        harborText.SetColor(sf::Color(0, 0, 0, 200));
        harborText.SetCenter(harborText.GetSize(), harborText.GetSize());
        harborText.SetPosition(pauseMenuSprite.GetPosition().x + 150 , pauseMenuSprite.GetPosition().y + 100);

        sf::String marketText("Market", scoreFont, 36);
        marketText.SetColor(sf::Color(0, 0, 0, 200));
        marketText.SetCenter(marketText.GetSize(), marketText.GetSize());
        marketText.SetPosition(pauseMenuSprite.GetPosition().x + 150 , pauseMenuSprite.GetPosition().y + 150);

        sf::String leaveHarborText("Leave harbor", scoreFont, 36);
        leaveHarborText.SetColor(sf::Color(0, 0, 0, 200));
        leaveHarborText.SetCenter(leaveHarborText.GetSize(), leaveHarborText.GetSize());
        leaveHarborText.SetPosition(pauseMenuSprite.GetPosition().x + 150 , pauseMenuSprite.GetPosition().y + 200);

        window->Draw(harborText);
        window->Draw(marketText);
        window->Draw(leaveHarborText);

        if(harborSelect == ENTER_MARKET)
        {
            pauseSkullSprite.SetPosition(pauseMenuSprite.GetPosition().x + 50 , pauseMenuSprite.GetPosition().y + 120);
        }
        else if(harborSelect == EXIT_HARBOR)
        {
            pauseSkullSprite.SetPosition(pauseMenuSprite.GetPosition().x + 50 , pauseMenuSprite.GetPosition().y + 170);
        }
        window->Draw(pauseSkullSprite);
    }

    else if(gameState == MARKET)
    {
        window->Clear();
        window->Draw(seaSprite);
        window->Draw(pauseMenuSprite);

        sf::String marketText("MARKET", scoreFont, 42);
        marketText.SetColor(sf::Color(0, 0, 0, 200));
        marketText.SetCenter(marketText.GetSize(), marketText.GetSize());
        marketText.SetPosition(pauseMenuSprite.GetPosition().x + 150 , pauseMenuSprite.GetPosition().y + 100);

        sf::String repairText("Repair ship", scoreFont, 36);
        repairText.SetColor(sf::Color(0, 0, 0, 200));
        repairText.SetCenter(repairText.GetSize(), repairText.GetSize());
        repairText.SetPosition(pauseMenuSprite.GetPosition().x + 150 , pauseMenuSprite.GetPosition().y + 150);

        sf::String upgradeText("Upgrade cannons", scoreFont, 36);
        upgradeText.SetColor(sf::Color(0, 0, 0, 200));
        upgradeText.SetCenter(upgradeText.GetSize(), upgradeText.GetSize());
        upgradeText.SetPosition(pauseMenuSprite.GetPosition().x + 150 , pauseMenuSprite.GetPosition().y + 200);

        sf::String leaveMarketText("Leave market", scoreFont, 36);
        leaveMarketText.SetColor(sf::Color(0, 0, 0, 200));
        leaveMarketText.SetCenter(leaveMarketText.GetSize(), leaveMarketText.GetSize());
        leaveMarketText.SetPosition(pauseMenuSprite.GetPosition().x + 150 , pauseMenuSprite.GetPosition().y + 250);

        window->Draw(marketText);
        window->Draw(repairText);
        window->Draw(upgradeText);
        window->Draw(leaveMarketText);

        if(marketSelect == REPAIR)
        {
            pauseSkullSprite.SetPosition(pauseMenuSprite.GetPosition().x + 50 , pauseMenuSprite.GetPosition().y + 120);
        }
        else if(marketSelect == UPGRADE)
        {
            pauseSkullSprite.SetPosition(pauseMenuSprite.GetPosition().x + 50 , pauseMenuSprite.GetPosition().y + 170);
        }
        else if(marketSelect == EXIT_MARKET)
        {
            pauseSkullSprite.SetPosition(pauseMenuSprite.GetPosition().x + 50 , pauseMenuSprite.GetPosition().y + 220);
        }
        window->Draw(pauseSkullSprite);
    }

    else if(gameState == PAUSED)
    {
        window->Clear();

        window->Draw(seaSprite);

        window->Draw(pauseMenuSprite);

        sf::String pausedText("PAUSED", scoreFont, 42);
        pausedText.SetColor(sf::Color(0, 0, 0, 200));
        pausedText.SetCenter(pausedText.GetSize(), pausedText.GetSize());
        pausedText.SetPosition(pauseMenuSprite.GetPosition().x + 150 , pauseMenuSprite.GetPosition().y + 100);

        sf::String resumeText("Resume", scoreFont, 36);
        resumeText.SetColor(sf::Color(0, 0, 0, 200));
        resumeText.SetCenter(resumeText.GetSize(), resumeText.GetSize());
        resumeText.SetPosition(pauseMenuSprite.GetPosition().x + 150 , pauseMenuSprite.GetPosition().y + 150);

        sf::String mainmenuText("Main Menu", scoreFont, 36);
        mainmenuText.SetColor(sf::Color(0, 0, 0, 200));
        mainmenuText.SetCenter(mainmenuText.GetSize(), mainmenuText.GetSize());
        mainmenuText.SetPosition(pauseMenuSprite.GetPosition().x + 150 , pauseMenuSprite.GetPosition().y + 200);

        window->Draw(pausedText);
        window->Draw(resumeText);
        window->Draw(mainmenuText);

        if(pauseSelect == RESUME)
        {
            pauseSkullSprite.SetPosition(pauseMenuSprite.GetPosition().x + 50 , pauseMenuSprite.GetPosition().y + 120);
        }
        else if(pauseSelect == MENU)
        {
            pauseSkullSprite.SetPosition(pauseMenuSprite.GetPosition().x + 50 , pauseMenuSprite.GetPosition().y + 170);
        }
        window->Draw(pauseSkullSprite);
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

    if(textBox != NULL && textBox->GetTime() < 2)
        textBox->Draw(*window);

    window->Display();
}
