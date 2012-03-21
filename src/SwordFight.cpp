#include <iostream>
#include "../include/SwordFight.h"

SwordFight::SwordFight(sf::RenderWindow *ewindow) :
    running(true)
{
    bgImage.LoadFromFile("images/swordFightBg.png");
    bgSprite.SetImage(bgImage);
    bgSprite.SetPosition(0,0);

    player = new SwordMan(PLAYER);
    computer = new SwordMan(ENEMY);

    player->Turn(DEFENSE);
    computer->Turn(STRIKE);

    player->SetDrawArea(2,0);
    computer->SetDrawArea(2,0);

    gameState = PLAY;

    deltaX = 0;

    window = ewindow;

    turnTimer.Reset();
}

SwordFight::~SwordFight()
{
    delete player;
    delete computer;
}

bool SwordFight::Fight()
{
    GameLoop();
    return winner;
}

void SwordFight::GameLoop()
{
    while(running)
    {
        LoopKeys();
        Update();
        Draw();
    }
}

void SwordFight::Draw()
{
    window->Draw(bgSprite);
    player->Draw(*window);
    computer->Draw(*window);

    window->Display();
}

void SwordFight::Update()
{
    /* GameState checks */
    if(enter && gameState == PAUSE) Lose();

    /* Take player choise */
    if((right && !space) && deltaX > 80) player->Move(RIGHT);
    else if(left && !space) player->Move(LEFT);
    else if(right && !space) player->Defence(MIDDLE);
    else if(up && !space) player->Defence(UP);
    else if(down && !space) player->Defence(DOWN);
    else if(right && space) player->Strike(MIDDLE);
    else if(up && space) player->Strike(UP);
    else if(down && space) player->Strike(DOWN);
    else player->DoNothing(); // Do nothing
    playerChoise = player->GetChoise();

    /* Take computer choise */
    aiChoise = rand()%5;
    if(aiChoise < 2 && deltaX > 80)
    {
        computer->Move(aiChoise);
    }

    if(computer->GetTurn() == DEFENSE && turnTimer.GetElapsedTime() > 1.0f)
        computer->Defence(aiChoise);
    else if(turnTimer.GetElapsedTime() > 1.0f)
        computer->Strike(aiChoise);

    /* Calculate if player and computer are in hitting range after movement */
    deltaX = computer->GetXpos() - (player->GetXpos() + player->GetWidth()/2);
    std::cout << "                     " << deltaX << std::endl;

    /*
     * TurnTimer prevents that players can't strike too thick
     * and swap strike turn
     */
    if(deltaX < 85 && turnTimer.GetElapsedTime() > 1.0f)
    {
        turnTimer.Reset();
        if(player->GetTurn() == DEFENSE)
        {
            if(playerChoise == -aiChoise)
            {
            }

            if(playerChoise != -aiChoise)
            {
                if(aiChoise != DO_NOTHING)
                {
                    player->GetHit();
                }
            }
        }
        else // player turn to strike
        {
            if(playerChoise != -aiChoise && playerChoise > 0)
            {
                if(playerChoise != DO_NOTHING)
                {
                    computer->GetHit();
                }
            }
        }



        SwapTurns();
        playerChoise = DO_NOTHING;
        aiChoise = DO_NOTHING;
    }
    /*
     * Reset timer if neither players doesn't strike
     * in time and swap strike turn
     */
    if(turnTimer.GetElapsedTime() > 1.0f)
    {
        turnTimer.Reset();
        SwapTurns();
    }

std::cout << "Player: " << player->GetHealth() << " Enemy: " << computer->GetHealth() << std::endl;
    /* Swap frame area from defense to attack and vice versa */
    if(player->GetTurn() == DEFENSE)
        player->SetDrawArea(2,0);
    else
        player->SetDrawArea(2,1);

    if(computer->GetTurn() == DEFENSE)
        computer->SetDrawArea(2,0);
    else
        computer->SetDrawArea(2,1);
}

void SwordFight::SwapTurns()
{
    if(player->GetTurn() == DEFENSE)
    {
        player->Turn(STRIKE);
        computer->Turn(DEFENSE);
    }
    else
    {
        player->Turn(DEFENSE);
        computer->Turn(STRIKE);
    }
}

void SwordFight::Lose()
{
    winner = ENEMY;
    running = false;
}

void SwordFight::Win()
{
    winner = PLAYER;
    running = false;
}

void SwordFight::LoopKeys()
{
    while(window->GetEvent(event))
    {
        if(event.Type == sf::Event::Closed)
        {
            window->Close();
        }

        if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)
        {
            SwapState();
        }
    }

    const sf::Input& Input = window->GetInput();
    left = Input.IsKeyDown(sf::Key::Left);
    right = Input.IsKeyDown(sf::Key::Right);
    up = Input.IsKeyDown(sf::Key::Up);
    down = Input.IsKeyDown(sf::Key::Down);
    enter = Input.IsKeyDown(sf::Key::Return);
    space = Input.IsKeyDown(sf::Key::Space);
}

void SwordFight::SwapState()
{
    if(gameState == PLAY)
        gameState = PAUSE;
    else
        gameState = PLAY;
}
