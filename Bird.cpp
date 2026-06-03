#include "Bird.h"

Bird::Bird(Texture &texture) {
    sprite.setTexture(texture);
    sprite.setScale(0.25f, 0.25f);
    sprite.setPosition(350, 500);

    velocity = 0;
    gravity = 1000.0f;
    flapPower = -450.0f;
}

void Bird::flap() {
    velocity = flapPower;
}

void Bird::update(float dt) {
    velocity += gravity * dt;
    sprite.move(0, velocity * dt);

    if (velocity < 0)
        sprite.setRotation(-20);
    else
        sprite.setRotation(20);
}

void Bird::reset() {
    sprite.setPosition(350, 500);
    velocity = 0;
    sprite.setRotation(0);
}

void Bird::draw(RenderWindow &window) {
    window.draw(sprite);
}

FloatRect Bird::getBounds() {
    return sprite.getGlobalBounds();
}

Vector2f Bird::getPosition() {
    return sprite.getPosition();
}