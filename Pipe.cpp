#include "Pipe.h"
#include <cstdlib>
#include <cmath>

Pipe::Pipe(Texture &texture, float x, Difficulty difficulty) {
    topPipe.setTexture(texture);
    bottomPipe.setTexture(texture);

    topPipe.setScale(1.0f, -1.0f);
    bottomPipe.setScale(1.0f, 1.0f);

    scored = false;

    if (difficulty == Difficulty::EASY) {
        gap = 380.0f;
        speed = 320.0f;
        oscillate = false;
        oscillationSpeed = 0.0f;
        oscillationRange = 0.0f;
    }
    else if (difficulty == Difficulty::MEDIUM) {
        gap = 300.0f;
        speed = 420.0f;
        oscillate = true;
        oscillationSpeed = 2.0f;
        oscillationRange = 50.0f;
    }
    else {
        gap = 240.0f;
        speed = 520.0f;
        oscillate = true;
        oscillationSpeed = 3.5f;
        oscillationRange = 100.0f;
    }

    centerY = (rand() % 500) + 250;

    topPipe.setPosition(x, centerY - gap / 2);
    bottomPipe.setPosition(x, centerY + gap / 2);
}

void Pipe::update(float dt, float totalTime) {
    topPipe.move(-speed * dt, 0);
    bottomPipe.move(-speed * dt, 0);

    if (oscillate) {
        float x = topPipe.getPosition().x;
        float offsetY = sin(totalTime * oscillationSpeed) * oscillationRange;

        topPipe.setPosition(x, centerY - gap / 2 + offsetY);
        bottomPipe.setPosition(x, centerY + gap / 2 + offsetY);
    }
}

void Pipe::draw(RenderWindow &window) {
    window.draw(topPipe);
    window.draw(bottomPipe);
}

bool Pipe::isOffScreen() {
    return topPipe.getPosition().x < -200;
}

bool Pipe::checkCollision(FloatRect birdBounds) {
    return birdBounds.intersects(topPipe.getGlobalBounds()) ||
           birdBounds.intersects(bottomPipe.getGlobalBounds());
}

bool Pipe::passedBird(float birdX) {
    if (!scored && topPipe.getPosition().x + topPipe.getGlobalBounds().width < birdX) {
        scored = true;
        return true;
    }

    return false;
}