#pragma once

#include "boss.h"
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <SDL_image.h>
#include <cmath>
#include <SDL_mixer.h>
#include<SDL_TTF.h>

using namespace std;

extern int SCREEN_WIDTH ;
extern int SCREEN_HEIGHT ;
extern int UPGRADE_DROP_CHANCE ;
extern int PLAYER_SPEED ;
extern int BULLET_SPEED ;
extern int BULLET_SIZE ;
extern int BULLET_QUANTITY ;
extern int BULLET_POWER;
extern int ENEMY_SPEED ;
extern int ENEMY_SPAWN_RATE ;
extern int ENEMY_HEALTH;
extern int BOSS_HEALTH ;
extern int BOSS_SPEED;
extern int BOSS_BULLET_SPEED ;
extern int BOSS_BULLET_SIZE ;
extern int ENEMY_BULLET_SIZE ;
extern int ENEMY_BULLET_SPEED  ;
extern int ENEMYFIRE_SPAWN_RATE ;
extern int upgradeCount ;
extern int nextUpgradeLevel ;
extern int bgY1 ;
extern int bgY2 ;
extern int playerX ;
extern int playerY;
extern int score ;
extern int frameCount ;
extern int bossCount ;
extern bool canShoot;
extern bool running ;
extern bool menu ;
extern SDL_Texture* bossBulletTexture;
extern SDL_Texture* enemiesFireBulletTexture;
extern SDL_Texture* enemiesTexture;
extern SDL_Texture* enemiesFireTexture;
extern SDL_Texture* playerTexture;
extern SDL_Texture* upgradeTexture;
extern SDL_Texture* menuTexture;
extern SDL_Texture* backgroundTexture;
extern SDL_Texture* bossTexture[3];
extern SDL_Texture* currentBossTexture;
extern SDL_Texture* bulletTextures[5];
extern SDL_Texture* currentBulletTexture;
extern Mix_Chunk* soundEffect;
extern Mix_Chunk* boomEffect;
extern Mix_Chunk* dieEffect;
extern Mix_Chunk* bossDieEffect;
extern Mix_Chunk* upgradeEffect;
extern Mix_Music* bgMusic;
extern TTF_Font* font;
extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern SDL_Rect playButton ;
extern Boss* boss ;
extern std::vector<Bullet> bullets;
extern std::vector<Bullet> bossBullets;
extern std::vector<Bullet> enemiesFireBullets;
extern std::vector<Enemy> enemies;
extern std::vector<EnemyFire> enemiesFire;
extern std::vector<Upgrade> upgrades;

void setTexture();
void startGame();
