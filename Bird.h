#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Bird {
private:
    Sprite sprite;
    float velocity;
    float gravity;
    float flapPower;

public:
    Bird(Texture &texture);

    void flap();
    void update(float dt);
    void reset();
    void draw(RenderWindow &window);

    FloatRect getBounds();
    Vector2f getPosition();
};

#endif