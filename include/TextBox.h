#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "../include/Drawable.h"

class TextBox : public Drawable
{
    public:
        TextBox(float posx, float posy, std::string text); /* Constructor takes x,y position and text to show */
        ~TextBox();
        void Update() {}
        void Draw(sf::RenderWindow &window);
        int GetTime() {return timer.GetElapsedTime(); }
    private:
        sf::Clock timer;
        std::string text;
    protected:

};

#endif // end of TEXTBOX_H
