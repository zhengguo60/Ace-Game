#ifndef ENTITY_H
#define ENTITY_H

#include <string>

// 基类
class Entity {
public:
    int x, y;
    std::string symbol;

    Entity(int startX, int startY, std::string sym);
    virtual ~Entity() {}
    virtual void move() = 0; // 纯虚函数
};

// 玩家类
class Player : public Entity {
public:
    Player(int startX, int startY);
    void move() override; // 玩家移动由输入控制，这里仅占位
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};

// 敌人类
class Enemy : public Entity {
public:
    Enemy(int startX, int startY);
    void move() override;
};

// 子弹类
class Bullet : public Entity {
public:
    Bullet(int startX, int startY);
    void move() override;
};
class Item : public Entity {
public:
    int type; // 0: 全屏炸弹(Bomb), 1: 散弹枪(Super)
    Item(int startX, int startY, int t);
    void move() override;
};
#endif