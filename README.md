# 🐦 Flappy Bird Game (C++ & SFML)

A fun and interactive **Flappy Bird Clone** developed using **C++** and **SFML**. The game features multiple difficulty levels, animated obstacles, score tracking, sound effects, and a fullscreen arcade-style experience.

## 🚀 Features

* 🎮 Classic Flappy Bird gameplay
* 🏆 Score and High Score system
* 🎯 Three Difficulty Modes:

  * Easy
  * Medium
  * Hard
* 🌊 Dynamic moving pipes with oscillation effects
* 🔊 Sound effects and background music
* ⏸ Pause and Resume functionality
* 📺 Fullscreen gameplay (1920×1080)
* 💥 Collision detection system
* 🔄 Restart and Main Menu support
* 💾 High score saved using file handling

## 🛠 Technologies Used

* C++
* SFML Graphics
* SFML Audio
* Object-Oriented Programming (OOP)
* File Handling

## 📂 Project Structure

```text
FlappyBird/
│
├── Bird.h
├── Bird.cpp
├── Pipe.h
├── Pipe.cpp
├── FlappyBird.cpp
├── highscore.txt
│
├── graphics/
│   ├── bird.png
│   └── pipe.png
│
├── sound/
│   ├── flap.wav
│   ├── hit.wav
│   └── music.mp3
│
└── font/
    └── KOMIKAP_.ttf
```

## 🎮 Controls

| Key   | Action         |
| ----- | -------------- |
| Space | Flap           |
| P     | Pause / Resume |
| 1     | Easy Mode      |
| 2     | Medium Mode    |
| 3     | Hard Mode      |
| Enter | Return to Menu |
| ESC   | Exit Game      |

## ⚙️ Installation

1. Install SFML.
2. Clone the repository:

```bash
git clone https://github.com/your-username/flappy-bird-sfml.git
```

3. Compile:

```bash
g++ FlappyBird.cpp Bird.cpp Pipe.cpp -o FlappyBird \
-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

4. Run:

```bash
./FlappyBird
```

## 🎯 Gameplay

Guide the bird through incoming pipes while avoiding collisions. Earn points by successfully passing obstacles. The game becomes more challenging as you increase the difficulty level.

## 📸 Highlights

* Smooth bird physics with gravity and flap mechanics
* Animated pipe movement in higher difficulty modes
* Persistent high-score system
* Arcade-style fullscreen experience

## 👨‍💻 Author

**Rahul Ray**
Computer Science Engineering Student
SOA University (ITER)

---

⭐ If you like this project, consider giving it a star on GitHub!
