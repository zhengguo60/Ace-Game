#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib> 
#include <ctime>   
#include <unistd.h> 
#include <cmath>   

Game::Game(int w, int h) 
    : width(w), height(h), isRunning(true), score(0), difficulty(1), superFireTimer(0) {
    player = new Player(width / 2, height - 2);
    srand(time(0)); // 随机数种子
}

Game::~Game() {
    cleanup();
    delete player;
}

void Game::cleanup() {
    for (auto b : bullets) delete b;
    bullets.clear();
    for (auto e : enemies) delete e;
    enemies.clear();
    for (auto i : items) delete i;
    items.clear();
}

void Game::setDifficulty(int level) {
    if (level >= 1 && level <= 3) {
        difficulty = level;
    }
}

void Game::init() {
    Utils::hideCursor();
    Utils::setNonBlocking(true);
}

void Game::saveGame() {
    std::ofstream outFile("save.txt");
    if (outFile.is_open()) {
        outFile << score << " " << difficulty << std::endl;
        outFile.close();
    }
}

bool Game::loadGame() {
    std::ifstream inFile("save.txt");
    if (inFile.is_open()) {
        inFile >> score >> difficulty;
        inFile.close();
        return true;
    }
    return false;
}

void Game::spawnEnemy() {
    // 难度越高，生成概率越大
    int chance = 5 + (difficulty * 5); 
    if (rand() % 100 < chance) {
        int randX = (rand() % (width - 2)) + 1;
        enemies.push_back(new Enemy(randX, 1));
    }
}

void Game::spawnItem() {
    // 1% 的概率生成道具
    if (rand() % 100 < 1) { 
        int randX = (rand() % (width - 2)) + 1;
        int type = rand() % 2; // 0: Bomb, 1: Scatter
        items.push_back(new Item(randX, 1, type));
    }
}

void Game::activateBomb() {
    // 清除所有敌人并加分
    for (auto e : enemies) {
        delete e;
        score += 5; 
    }
    enemies.clear();
}

void Game::checkCollisions() {
    // 1. 子弹打敌人 
    for (auto itB = bullets.begin(); itB != bullets.end(); ) {
        bool hit = false;
        for (auto itE = enemies.begin(); itE != enemies.end(); ) {
            if ((*itB)->x == (*itE)->x && (*itB)->y == (*itE)->y) {
                // 碰撞发生
                delete *itB;
                delete *itE;
                itB = bullets.erase(itB);
                itE = enemies.erase(itE);
                score += 10 * difficulty;
                hit = true;
                break; 
            } else {
                ++itE;
            }
        }
        if (!hit) ++itB;
    }

    // 2. 敌人撞玩家 (宽松检测 abs <= 1)
    for (auto e : enemies) {
        if (e->x == player->x && std::abs(e->y - player->y) <= 1) {
            isRunning = false; 
        }
    }
}

void Game::handleInput() {
    char moveDir = 0; 
    while (Utils::kbhit()) {
        char c = Utils::getch();
        
        if (c == ' ') {
            // 普通子弹
            bullets.push_back(new Bullet(player->x, player->y - 1));
            
            // 散弹枪 Buff 逻辑
            if (superFireTimer > 0) {
                if(player->x > 1) 
                    bullets.push_back(new Bullet(player->x - 1, player->y - 1));
                if(player->x < width - 2) 
                    bullets.push_back(new Bullet(player->x + 1, player->y - 1));
            }
        }
        else if (c == 'q') isRunning = false;
        else if (c == 'p') saveGame();
        else if (c == 'w' || c == 's' || c == 'a' || c == 'd') moveDir = c;
    }

    if (moveDir == 'w') player->moveUp();
    else if (moveDir == 's') player->moveDown();
    else if (moveDir == 'a') player->moveLeft();
    else if (moveDir == 'd') player->moveRight();
}

void Game::update() {
    spawnEnemy();
    spawnItem();

    // 更新 Buff 计时器
    if (superFireTimer > 0) superFireTimer--;

    // === 1. 更新子弹 ===
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        (*it)->move();
        if ((*it)->y < 1) { 
            delete *it;
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }

    // 穿插检测 
    checkCollisions();

    // === 3. 更新敌人 ===
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        (*it)->move();
        if ((*it)->y >= height - 1) { 
            delete *it;
            it = enemies.erase(it);
            // score--; // 已注释掉扣分逻辑，避免 frustration
        } else {
            ++it;
        }
    }

    // === 4. 更新道具 & 拾取检测 ===
    for (auto it = items.begin(); it != items.end(); ) {
        (*it)->move();
        
        // 检查是否被玩家拾取 (宽松检测)
        if (std::abs((*it)->x - player->x) <= 1 && std::abs((*it)->y - player->y) <= 1) {
            // 触发效果
            Item* item = dynamic_cast<Item*>(*it);
            if (item) {
                if (item->type == 0) activateBomb();
                else if (item->type == 1) superFireTimer = 100; // 10秒左右
            }
            delete *it;
            it = items.erase(it);
        }
        // 检查是否掉出屏幕
        else if ((*it)->y >= height - 1) {
            delete *it;
            it = items.erase(it);
        } else {
            ++it;
        }
    }

    // 穿插检测
    checkCollisions();
}

void Game::render() {
    std::cout << "\033[H"; // 光标复位到左上角

    // 1. 准备缓冲区
    std::vector<std::string> buffer(height, std::string(width, ' '));

    // 填充实体
    if(player->y >= 0 && player->y < height && player->x >= 0 && player->x < width)
        buffer[player->y][player->x] = player->symbol[0];

    for(auto e : enemies) 
        if(e->y >= 0 && e->y < height && e->x >= 0 && e->x < width)
            buffer[e->y][e->x] = e->symbol[0];

    for(auto b : bullets) 
        if(b->y >= 0 && b->y < height && b->x >= 0 && b->x < width)
            buffer[b->y][b->x] = b->symbol[0];
            
    for(auto i : items)
        if(i->y >= 0 && i->y < height && i->x >= 0 && i->x < width)
            buffer[i->y][i->x] = i->symbol[0];

    // 2. 准备侧边栏内容
    std::vector<std::string> sideBar;
    sideBar.push_back(Utils::YELLOW + " === CONTROLS ===" + Utils::RESET);
    sideBar.push_back("");
    sideBar.push_back(Utils::CYAN + "  [W] " + Utils::RESET + "Move Up");
    sideBar.push_back(Utils::CYAN + "  [S] " + Utils::RESET + "Move Down");
    sideBar.push_back(Utils::CYAN + "  [A] " + Utils::RESET + "Move Left");
    sideBar.push_back(Utils::CYAN + "  [D] " + Utils::RESET + "Move Right");
    sideBar.push_back("");
    sideBar.push_back(Utils::RED   + "  [SPC]" + Utils::RESET + " Shoot");
    sideBar.push_back("");
    sideBar.push_back(Utils::GREEN + "  [P] " + Utils::RESET + "Save Game");
    sideBar.push_back(Utils::MAGENTA + "  [Q] " + Utils::RESET + "Quit Game");
    sideBar.push_back("");
    
    // 显示 Buff 状态
    if (superFireTimer > 0) {
        sideBar.push_back(Utils::GREEN + Utils::BOLD + " [!!!] SUPER GUN " + Utils::RESET);
        std::string bar = "";
        for(int k=0; k < superFireTimer/10; ++k) bar += "|";
        sideBar.push_back(Utils::GREEN + bar + Utils::RESET);
    }

    // 3. 绘制顶部
    std::cout << Utils::BLUE << "╔";
    for(int i=0; i<width; ++i) std::cout << "═"; 
    std::cout << "╗" << Utils::RESET << std::endl;

    std::cout << Utils::BLUE << "║" << Utils::RESET 
              << Utils::YELLOW << " SCORE: " << Utils::RESET << Utils::BOLD << score << Utils::RESET
              << "   "
              << Utils::CYAN << " LEVEL: " << Utils::RESET << difficulty;
    
    int printedLen = 25; 
    if (score > 9) printedLen++;
    if (score > 99) printedLen++;
    if (score > 999) printedLen++;
    for(int i=printedLen; i<width; ++i) std::cout << " "; 
    
    std::cout << Utils::BLUE << "║" << Utils::RESET << std::endl;

    std::cout << Utils::BLUE << "╠";
    for(int i=0; i<width; ++i) std::cout << "═";
    std::cout << "╣" << Utils::RESET << std::endl;

    // 4. 绘制游戏区域 + 侧边栏
    for(int y = 0; y < height; ++y) {
        std::cout << Utils::BLUE << "║" << Utils::RESET; // 左框

        for(int x = 0; x < width; ++x) {
            char c = buffer[y][x];
            if (c == 'A')      std::cout << Utils::BOLD << Utils::CYAN << "A" << Utils::RESET;
            else if (c == 'M') std::cout << Utils::RED << "M" << Utils::RESET;
            else if (c == '|') std::cout << Utils::YELLOW << "|" << Utils::RESET;
            else if (c == 'B' || c == 'S') std::cout << Utils::BOLD << Utils::GREEN << c << Utils::RESET;
            else               std::cout << " ";
        }

        std::cout << Utils::BLUE << "║" << Utils::RESET; // 右框

        // 绘制侧边栏
        if (static_cast<size_t>(y) < sideBar.size()) {
            std::cout << "  " << sideBar[y];
        }
        std::cout << std::endl;
    }

    // 5. 底部边框
    std::cout << Utils::BLUE << "╚";
    for(int i=0; i<width; ++i) std::cout << "═";
    std::cout << "╝" << Utils::RESET << std::endl;
}

void Game::run() {
    while (isRunning) {
        handleInput();
        update();
        render();
        usleep(100000); // 100ms
    }
    
    
    usleep(500000); // 0.5秒

    while(Utils::kbhit()) {
        Utils::getch();
    }

    Utils::clearScreen();
    
    std::string title = "=== GAME OVER ===";
    std::string scoreStr = "Final Score: " + std::to_string(score);
    std::string prompt = "Press ANY KEY to return to Menu...";
    
    int padTitle = (width - title.length()) / 2;
    int padScore = (width - scoreStr.length()) / 2;
    int padPrompt = (width - prompt.length()) / 2;

    for(int i=0; i<height/3; ++i) std::cout << std::endl;

    std::cout << Utils::RED << std::string(padTitle, ' ') << title << Utils::RESET << std::endl;
    std::cout << std::endl;
    std::cout << Utils::YELLOW << Utils::BOLD << std::string(padScore, ' ') << scoreStr << Utils::RESET << std::endl;
    std::cout << std::endl;
    std::cout << Utils::CYAN << std::string(padPrompt, ' ') << prompt << Utils::RESET << std::endl;

    while(!Utils::kbhit()) {
        usleep(100000); // 等待中...
    }
    Utils::getch(); // 消耗掉按下的那个键

    Utils::showCursor();
    Utils::setNonBlocking(false);
    
}