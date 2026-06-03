#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>
using namespace sf;

enum class Difficulty {
    EASY,
    MEDIUM,
    HARD
};

class Pipe {
private:
    Sprite topPipe;
    Sprite bottomPipe;
    bool scored;
    float speed;
    float gap;
    float centerY;
    bool oscillate;
    float oscillationSpeed;
    float oscillationRange;

public:
    Pipe(Texture &texture, float x, Difficulty difficulty);

    void update(float dt, float totalTime);
    void draw(RenderWindow &window);

    bool isOffScreen();
    bool checkCollision(FloatRect birdBounds);
    bool passedBird(float birdX);
};

#endif