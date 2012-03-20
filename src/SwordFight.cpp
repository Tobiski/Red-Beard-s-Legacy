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
    int THIS_IS_CURRENT_AI_CHOISE_RIGHT_NOW = rand()%7;
    /* GameState checks */
    if(escape)
    {
        if(gameState == PLAY) gameState = PAUSE;
        else gameState = PLAY;
    }
    if(enter && gameState == PAUSE) Lose();

    /* Fight check */
    deltaX = computer->GetXpos() - player->GetXpos() ;
    /* Take player choise */
    if((right && !space) && deltaX > 30) player->Move(RIGHT);
    else if(left && !space) player->Move(LEFT);
    else if(up && !space) player->Defence(UP);
    else if(down && !space) player->Defence(DOWN);
    else if(right && space) player->Strike(MIDDLE);
    else if(up && space) player->Strike(UP);
    else if(down && space) player->Strike(DOWN);
    else; // Do nothing
    /* Take computer choise */
    if(THIS_IS_CURRENT_AI_CHOISE_RIGHT_NOW == 0) computer->Move(RIGHT);
    else if(THIS_IS_CURRENT_AI_CHOISE_RIGHT_NOW == 1 && deltaX > 30) computer->Move(LEFT);
    else if(THIS_IS_CURRENT_AI_CHOISE_RIGHT_NOW == 2) computer->Defence(UP);
    else if(THIS_IS_CURRENT_AI_CHOISE_RIGHT_NOW == 3) computer->Defence(DOWN);
    else if(THIS_IS_CURRENT_AI_CHOISE_RIGHT_NOW == 4) computer->Strike(MIDDLE);
    else if(THIS_IS_CURRENT_AI_CHOISE_RIGHT_NOW == 5) computer->Strike(UP);
    else computer->Strike(DOWN);

    /* If player and computer are in hitting range */
    if(deltaX < 20)
    {
        playerChoise = player->GetChoise();
        aiChoise = computer->GetChoise();
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
