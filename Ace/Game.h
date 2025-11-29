#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Entity.h"

enum Difficulty { EASY = 1, MEDIUM = 2, HARD = 3 };

class Game {
private:
    int width, height;
    bool isRunning;
    int score;
    int difficulty;
    
    Player* player;
    std::vector<Entity*> bullets;
    std::vector<Entity*> enemies;

    void handleInput();
    void update();
    void render();
    void spawnEnemy();
    void checkCollisions();
    void cleanup(); 
    std::vector<Entity*> items; 
    int superFireTimer;     

    void spawnItem();        
    void activateBomb();      
public:
    Game(int w, int h);
    ~Game();

    void init();
    void run();
    void setDifficulty(int level);
    
    // 文件 I/O
    void saveGame();
    bool loadGame();
};

#endif