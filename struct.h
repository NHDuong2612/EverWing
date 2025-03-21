#ifndef STRUCT_H
#define STRUCT_H

#include<vector>
#include<SDL.h>

struct Bullet {
    int x, y,power;
};

struct Enemy {
    int x, y, health;
};

struct EnemyFire {
    int x, y, health;
};

struct Upgrade {
    int x, y;
};
struct Boss {
    int x, y, health;
    bool movingRight;

    Boss(int startX, int startY, int hp) : x(startX), y(startY), health(hp), movingRight(true) {}
    void move();
    void shoot(std::vector<Bullet>& bossBullets);
};
#endif
