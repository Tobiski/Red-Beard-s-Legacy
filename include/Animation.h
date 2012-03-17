#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "../include/Drawable.h"

class Animation : public Drawable
{
    public:
        Animation(float posx, float posy, float angle, std::string imgDir, int maxFrames);
        ~Animation();
        void Update();
        void Draw(sf::RenderWindow &window);
        int GetCurrentFrame() { return currentFrame; }
        int GetMaxFrames() { return maxFrames; }
    protected:

    private:
        int maxFrames;
        int currentFrame;
        sf::Clock frameTime;
};

#endif // end of _ANIMATION_H_
