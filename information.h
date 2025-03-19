#include <SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include<iostream>
#include<SDL_image.h>
#include<cmath>
#include<SDL_mixer.h>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int UPGRADE_DROP_CHANCE = 10;
int PLAYER_SPEED = 5;
int BULLET_SPEED = 8;
int BULLET_SIZE = 10;
int BULLET_QUANTITY = 1;
int BULLET_POWER = 2;
int ENEMY_SPEED = 3;
int ENEMY_SPAWN_RATE = 50;
int ENEMY_HEALTH = 5;
int BOSS_HEALTH = 400;
int BOSS_SPEED = 2;
int BOSS_BULLET_SPEED = 7;
int BOSS_BULLET_SIZE = 20;
int upgradeCount = 0;
int nextUpgradeLevel = 2;
int bgY1 = 0;
int bgY2 = -SCREEN_HEIGHT;

SDL_Texture* bossBulletTexture = nullptr;
SDL_Texture* enemiesTexture = nullptr;
SDL_Texture* playerTexture = nullptr;
SDL_Texture* upgradeTexture = nullptr;
SDL_Texture* menuTexture = nullptr;
SDL_Texture* bossTexture[3];
SDL_Texture* currentBossTexture;
SDL_Texture* bulletTextures[4];
SDL_Texture* currentBulletTexture;
Mix_Chunk* soundEffect = nullptr;
Mix_Chunk* boomEffect = nullptr;
Mix_Chunk* dieEffect = nullptr;
Mix_Chunk* bossDieEffect = nullptr;
struct Bullet {
    int x, y,power;
};

struct Enemy {
    int x, y, health;
};

struct Upgrade {
    int x, y;
};

struct Boss {
    int x, y, health;
    bool movingRight;
};

Boss* boss = nullptr;
std::vector<Bullet> bullets;
std::vector<Bullet> bossBullets;
std::vector<Enemy> enemies;
std::vector<Upgrade> upgrades;


