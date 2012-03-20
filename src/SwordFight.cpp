#include "../include/SwordFight.h"

SwordFight::SwordFight(sf::RenderWindow* ewindow) :
    window(ewindow), running(true)
{
    bgImage.LoadFromFile("images/sea.png");
    bgSprite.SetImage(bgImage);
    bgSprite.SetPosition(0,0);

    player = new SwordMan();
    computer = new SwordMan();

    deltaX = 0;

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
        draw();
    }
}

void SwordFight::draw()
{
    player->Draw(*window);
    computer->Draw(*window);
}

void SwordFight::Update()
{
    /* GameState checks */
    if(escape)
    {
        if(gameState == PLAY) gameState = PAUSE;
        else gameState = PLAY;
    }
    if(enter && gameState == PAUSE) Lose();


    /* Take player choise */
    if((right && !space) && deltaX > 30) player->Move(RIGHT);
    else if(left && !space) player->Move(LEFT);
    else if(up && !space) player->Defence(UP);
    else if(down && !space) player->Defence(DOWN);
    else if(right && space) player->Strike(MIDDLE);
    else if(up && space) player->Strike(UP);
    else if(down && space) player->Strike(DOWN);
    else; // Do nothing
    playerChoise = player->GetChoise();

    /* Take computer choise */
    aiChoise = rand()%7;
    if(aiChoise == 0) computer->Move(RIGHT);
    else if(aiChoise == 1 && deltaX > 30) computer->Move(LEFT);
    else if(aiChoise == 2) computer->Defence(UP);
    else if(aiChoise == 3) computer->Defence(DOWN);
    else if(aiChoise == 4) computer->Strike(MIDDLE);
    else if(aiChoise == 5) computer->Strike(UP);
    else computer->Strike(DOWN);

    /* Calculate if player and computer are in hitting range after movement */
    deltaX = computer->GetXpos() - (player->GetXpos() + player->GetWidth());

    /*
     * TurnTimer prevents that players can't strike too thick
     * and swap strike turn
     */
    if(deltaX < 20 && turnTimer.GetElapsedTime() > 30.0f)
    {
        turnTimer.Reset();
        if(player->GetTurn() == DEFENSE)
        {
            if(playerChoise != aiChoise)
            {
                player->LoseEnergy();
            }
        }
        else // player turn to strike
        {
            if(playerChoise != aiChoise)
            {
                computer->LoseEnergy();
            }
        }
        SwapTurns();
    }
    /*
     * Reset timer if neither players doesn't strike
     * in time and swap strike turn
     */
    if(turnTimer.GetElapsedTime() > 30.0f)
    {
        turnTimer.Reset();
        SwapTurns();
    }
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
    winner = COMPUTER;
    running = false;
}

void SwordFight::Win()
{
    winner = PLAYER;
    running = false;
}

void SwordFight::LoopKeys()
{
    const sf::Input& Input = window->GetInput();
    left = Input.IsKeyDown(sf::Key::Left);
    right = Input.IsKeyDown(sf::Key::Right);
    up = Input.IsKeyDown(sf::Key::Up);
    down = Input.IsKeyDown(sf::Key::Down);
    enter = Input.IsKeyDown(sf::Key::Return);
    escape = Input.IsKeyDown(sf::Key::Escape);
}
