#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Bird.h"
#include "Pipe.h"

using namespace sf;
using namespace std;

int loadHighScore() {
    ifstream file("highscore.txt");
    int highScore = 0;

    if (file.is_open()) {
        file >> highScore;
        file.close();
    }

    return highScore;
}

void saveHighScore(int highScore) {
    ofstream file("highscore.txt");

    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}

void centerText(Text &text, float x, float y) {
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin(
        textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f
    );
    text.setPosition(x, y);
}

void startGame(
    Bird &bird,
    vector<Pipe> &pipes,
    Texture &texturePipe,
    Difficulty difficulty,
    int &score,
    float &totalTime,
    float &pipeTimer,
    bool &inMenu,
    bool &paused,
    bool &gameOver,
    Clock &clock
) {
    inMenu = false;
    paused = false;
    gameOver = false;

    score = 0;
    totalTime = 0;
    pipeTimer = 0;

    bird.reset();
    pipes.clear();
    pipes.push_back(Pipe(texturePipe, 1920, difficulty));

    clock.restart();
}

int main() {
    srand((int)time(0));

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Flappy Bird!!!", Style::Fullscreen);
    window.setFramerateLimit(60);

    Texture textureBird;
    Texture texturePipe;

    if (!textureBird.loadFromFile("graphics/bird.png")) {
        cout << "Failed to load graphics/bird.png" << endl;
        return -1;
    }

    if (!texturePipe.loadFromFile("graphics/pipe.png")) {
        cout << "Failed to load graphics/pipe.png" << endl;
        return -1;
    }

    Font font;
    if (!font.loadFromFile("font/KOMIKAP_.ttf")) {
        cout << "Failed to load font/KOMIKAP_.ttf" << endl;
        return -1;
    }

    SoundBuffer flapBuffer;
    SoundBuffer hitBuffer;
    Sound flapSound;
    Sound hitSound;
    Music backgroundMusic;

    if (flapBuffer.loadFromFile("sound/flap.wav"))
        flapSound.setBuffer(flapBuffer);

    if (hitBuffer.loadFromFile("sound/hit.wav"))
        hitSound.setBuffer(hitBuffer);

    if (backgroundMusic.openFromFile("sound/music.mp3")) {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(35);
        backgroundMusic.play();
    }

    Bird bird(textureBird);
    vector<Pipe> pipes;

    Difficulty difficulty = Difficulty::EASY;

    bool inMenu = true;
    bool paused = true;
    bool gameOver = false;
    bool acceptInput = true;

    int score = 0;
    int highScore = loadHighScore();

    float totalTime = 0;
    float pipeTimer = 0;

    Clock clock;

    Text menuText;
    Text messageText;
    Text scoreText;
    Text highScoreText;
    Text infoText;

    menuText.setFont(font);
    messageText.setFont(font);
    scoreText.setFont(font);
    highScoreText.setFont(font);
    infoText.setFont(font);

    menuText.setCharacterSize(70);
    messageText.setCharacterSize(70);
    scoreText.setCharacterSize(60);
    highScoreText.setCharacterSize(45);
    infoText.setCharacterSize(35);

    menuText.setFillColor(Color::Black);
    messageText.setFillColor(Color::Red);
    scoreText.setFillColor(Color::Black);
    highScoreText.setFillColor(Color::Black);
    infoText.setFillColor(Color::Blue);

    menuText.setString(
        "FLAPPY BIRD\n\n"
        "Select Difficulty\n\n"
        "Press 1 : Easy\n"
        "Press 2 : Medium\n"
        "Press 3 : Hard\n\n"
        "ESC : Exit"
    );
    centerText(menuText, 1920 / 2.0f, 1080 / 2.0f);

    scoreText.setPosition(60, 40);
    highScoreText.setPosition(1350, 45);
    infoText.setPosition(420, 1000);

    RectangleShape ground;
    ground.setSize(Vector2f(1920, 90));
    ground.setFillColor(Color(160, 90, 40));
    ground.setPosition(0, 990);

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyReleased)
                acceptInput = true;
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        if (inMenu) {
            if (Keyboard::isKeyPressed(Keyboard::Num1)) {
                difficulty = Difficulty::EASY;
                startGame(bird, pipes, texturePipe, difficulty, score, totalTime,
                          pipeTimer, inMenu, paused, gameOver, clock);
            }

            if (Keyboard::isKeyPressed(Keyboard::Num2)) {
                difficulty = Difficulty::MEDIUM;
                startGame(bird, pipes, texturePipe, difficulty, score, totalTime,
                          pipeTimer, inMenu, paused, gameOver, clock);
            }

            if (Keyboard::isKeyPressed(Keyboard::Num3)) {
                difficulty = Difficulty::HARD;
                startGame(bird, pipes, texturePipe, difficulty, score, totalTime,
                          pipeTimer, inMenu, paused, gameOver, clock);
            }
        }

        if (!inMenu && gameOver && Keyboard::isKeyPressed(Keyboard::Return)) {
            inMenu = true;
            paused = true;
            gameOver = false;
            centerText(menuText, 1920 / 2.0f, 1080 / 2.0f);
        }

        if (!inMenu && !gameOver && Keyboard::isKeyPressed(Keyboard::P) && acceptInput) {
            paused = !paused;
            acceptInput = false;

            if (paused) {
                messageText.setString("PAUSED\nPress P to Resume");
                centerText(messageText, 1920 / 2.0f, 1080 / 2.0f);
            }
        }

        if (!inMenu && !paused && !gameOver &&
            Keyboard::isKeyPressed(Keyboard::Space) && acceptInput) {
            bird.flap();
            flapSound.play();
            acceptInput = false;
        }

        Time dt = clock.restart();

        if (!inMenu && !paused && !gameOver) {
            float deltaTime = dt.asSeconds();

            totalTime += deltaTime;
            pipeTimer += deltaTime;

            bird.update(deltaTime);

            if (pipeTimer > 2.2f) {
                pipes.push_back(Pipe(texturePipe, 1920, difficulty));
                pipeTimer = 0;
            }

            for (int i = 0; i < pipes.size(); i++) {
                pipes[i].update(deltaTime, totalTime);

                if (pipes[i].passedBird(bird.getPosition().x)) {
                    score++;
                }

                if (pipes[i].checkCollision(bird.getBounds())) {
                    gameOver = true;
                    paused = true;
                    hitSound.play();

                    if (score > highScore) {
                        highScore = score;
                        saveHighScore(highScore);
                    }

                    messageText.setString("GAME OVER!\nPress ENTER for Menu");
                    centerText(messageText, 1920 / 2.0f, 1080 / 2.0f);
                }
            }

            if (!pipes.empty() && pipes[0].isOffScreen()) {
                pipes.erase(pipes.begin());
            }

            if (bird.getBounds().top < 0 ||
                bird.getBounds().top + bird.getBounds().height > 990) {
                gameOver = true;
                paused = true;
                hitSound.play();

                if (score > highScore) {
                    highScore = score;
                    saveHighScore(highScore);
                }

                messageText.setString("GAME OVER!\nPress ENTER for Menu");
                centerText(messageText, 1920 / 2.0f, 1080 / 2.0f);
            }
        }

        stringstream ss;
        ss << "SCORE: " << score;
        scoreText.setString(ss.str());

        stringstream hs;
        hs << "HIGH SCORE: " << highScore;
        highScoreText.setString(hs.str());

        string diffName;
        if (difficulty == Difficulty::EASY)
            diffName = "EASY";
        else if (difficulty == Difficulty::MEDIUM)
            diffName = "MEDIUM";
        else
            diffName = "HARD";

        infoText.setString("Difficulty: " + diffName + "     SPACE: Flap     P: Pause     ESC: Exit");

        window.clear(Color::White);

        if (inMenu) {
            window.draw(menuText);
        }
        else {
            for (int i = 0; i < pipes.size(); i++) {
                pipes[i].draw(window);
            }

            bird.draw(window);
            window.draw(ground);
            window.draw(scoreText);
            window.draw(highScoreText);
            window.draw(infoText);

            if (paused) {
                window.draw(messageText);
            }
        }

        window.display();
    }

    return 0;
}