#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>


class Drawable
{
    public:

        Drawable();
        virtual ~Drawable();
        virtual void update() = 0;

        void Draw(sf::RenderWindow &window);
        int GetArea();

        /* Getters */
        float GetXpos() { return posx; }
        float GetYpos() { return posy; }
        float GetAccel(){ return accel;}
        float GetRotation() { return rotationAngle; }
        float GetWidth(){ return sprite.GetSize().x;}
        float GetHeight(){ return sprite.GetSize().y;}

    protected:
    private:
        sf::Image image;
        sf::Sprite sprite;
        sf::Clock spawnTime;
        float posx;
        float posy;
        float accel;
        float speedx;
        float speedy;
        float rotationAngle;
};

#endif // DRAWABLE_H
