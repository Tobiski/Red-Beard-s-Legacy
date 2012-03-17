#include <iostream>
#include "../include/Animation.h"
#include "../include/Misc.h"

Animation::Animation(float posx, float posy, float angle, std::string imgDir, int maxFrames)
{
    this->posx = posx;
    this->posy = posy;
    this->angle = angle;
    image.LoadFromFile(imgDir);
    image.SetSmooth(false);
    sprite.SetImage(image);
    sprite.SetCenter(20, 40);
    sprite.SetRotation(angle*-1);
    sprite.SetPosition(posx, posy);
    currentFrame = 0;
    this->maxFrames = maxFrames;
    frameTime.Reset();
}

Animation::~Animation()
{

}

void Animation::Update()
{
    if(currentFrame < maxFrames && frameTime.GetElapsedTime() > 1/(MAX_FPS / maxFrames))
    {
        currentFrame++;
        frameTime.Reset();
    }
}

void Animation::Draw(sf::RenderWindow &window)
{
    sf::IntRect drawArea(currentFrame*40, 0, currentFrame*40 + 40, 80);
    sprite.SetSubRect(drawArea);
    sprite.SetPosition(posx, posy);


    window.Draw(sprite);
}
