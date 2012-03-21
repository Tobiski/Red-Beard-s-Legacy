#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>


class Drawable
{
    public:
        Drawable();
        virtual ~Drawable();
        virtual void Update() = 0;

        void Draw(sf::RenderWindow &window);
        int GetArea();
        void GetHit() { health--; }
        void SetDrawArea(int maxFrames, int frame);

        /* Getters */
        int GetHealth() { return health; }
        float GetXpos() { return posx; }
        float GetYpos() { return posy; }
        float GetAccel(){ return accel;}
        float GetRotation() { return angle; }
        float GetWidth(){ return sprite.GetSize().x; }
        float GetHeight(){ return sprite.GetSize().y; }
        sf::Sprite GetSprite() { return sprite; }

        /* Settlers */
        void SetHealth(int h) { health = h; }
        void SetposX(float x) { posx = x; }
        void SetposY(float y) { posy = y; }
        void SetSpeedX(float x) { speedx = x; }
        void SetSpeedY(float y) { speedy = y; }
        void SetRotation(float rot) { angle = rot; }
        void SetAcceleration(float acc) { accel = acc; }

    protected:
        sf::Image image;
        sf::Sprite sprite;
        sf::Clock spawnTime;
        float posx;
        float posy;
        float accel;
        float speedx;
        float speedy;
        float angle;
        int health;
};

#endif // DRAWABLE_H
