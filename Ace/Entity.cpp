#include "Entity.h"


Entity::Entity(int startX, int startY, std::string sym) 
    : x(startX), y(startY), symbol(sym) {}

// 使用 'A' 看起来更像飞机的尖头，或者使用 'W' 代表双翼
Player::Player(int startX, int startY) : Entity(startX, startY, "A") {} 
void Player::move() {} 
void Player::moveLeft() { if(x > 1) x--; }
void Player::moveRight() { if(x < 48) x++; } 
void Player::moveUp() { if(y > 1) y--; }
void Player::moveDown() { if(y < 18) y++; }

// 使用 'M' 或 'V' 看起来像倒置的飞船
Enemy::Enemy(int startX, int startY) : Entity(startX, startY, "M") {}
void Enemy::move() {
    y++; 
}

// 使用 '|' 即可
Bullet::Bullet(int startX, int startY) : Entity(startX, startY, "|") {}
void Bullet::move() {
    y--; 
}
Item::Item(int startX, int startY, int t) 
    : Entity(startX, startY, t == 0 ? "B" : "S"), type(t) {}

void Item::move() {
    y++; // 道具向下掉落
}