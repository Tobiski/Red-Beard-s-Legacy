#include "../include/SwordFight.h"

SwordFight::SwordFight(sf::RenderWindow* ewindow) :
    window(ewindow), running(true)
{
    bgImage.LoadFromFile("images/sea.png");
    bgSprite.SetImage(bgImage);
    bgSprite.SetPosition(0,0);

    player = new SwordMan();
    computer = new SwordMan();
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
    }
}

void SwordFight::Update()
{
    if(right && !space) player->Move(RIGHT);
    if(left && !space) player->Move(LEFT);
    if(up && !space) player->Defence(UP);
    if(down && !space) player->Defence(DOWN);
    if(right && space) player->Strike(UP);
    if(up && space) player->Strike(MIDDLE);
    if(down && space) player->Strike(DOWN);

    if(escape)
    {
        if(gameState == PLAY) gameState = PAUSE;
        else gameState = PLAY;
    }

    if(enter && gameState == PAUSE) Lose();
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
