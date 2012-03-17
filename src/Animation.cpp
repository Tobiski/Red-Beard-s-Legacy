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
    sprite.SetRotation(angle);
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
    if(currentFrame < maxFrames)
        currentFrame++;

    std::cout << "Updating animation\n" << std::endl;
}
