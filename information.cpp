
#include "information.h"
#include "loadTexture.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
int UPGRADE_DROP_CHANCE = 15;
int PLAYER_SPEED = 5;
int BULLET_SPEED = 8;
int BULLET_SIZE = 10;
int BULLET_QUANTITY = 1;
int BULLET_POWER = 2;
int ENEMY_SPEED = 3;
int ENEMY_SPAWN_RATE = 50;
int ENEMY_HEALTH = 4;
int BOSS_HEALTH = 500;
int BOSS_SPEED = 2;
int BOSS_BULLET_SPEED = 7;
int BOSS_BULLET_SIZE = 20;
int ENEMY_BULLET_SIZE = 20;
int ENEMY_BULLET_SPEED = 7;
int ENEMYFIRE_SPAWN_RATE = 50;
int upgradeCount = 0;
int nextUpgradeLevel = 2;
int bgY1 = 0;
int bgY2 = -SCREEN_HEIGHT;
int playerX = SCREEN_WIDTH / 2 - 25;
int playerY = SCREEN_HEIGHT - 80;
int score = 0;
int frameCount ;
int bossCount = 0;

bool canShoot = true;
bool running = false;
bool menu = true;

SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;
SDL_Texture* backgroundTexture = nullptr;
SDL_Texture* menuTexture = nullptr;
SDL_Texture* bulletTextures[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
SDL_Texture* currentBulletTexture = nullptr;
SDL_Texture* playerTexture = nullptr;
SDL_Texture* upgradeTexture = nullptr;
SDL_Texture* enemiesTexture = nullptr;
SDL_Texture* enemiesFireTexture = nullptr;
SDL_Texture* enemiesFireBulletTexture = nullptr;
SDL_Texture* bossTexture[3] = {nullptr, nullptr, nullptr};
SDL_Texture* bossBulletTexture = nullptr;
SDL_Texture* currentBossTexture = nullptr;

Mix_Chunk* soundEffect = nullptr;
Mix_Chunk* boomEffect = nullptr;
Mix_Chunk* dieEffect = nullptr;
Mix_Chunk* bossDieEffect = nullptr;
Mix_Chunk* upgradeEffect = nullptr;
Mix_Music* bgMusic = nullptr;

TTF_Font* font = nullptr;

SDL_Rect playButton = {300, 300, 180,40};
Boss* boss = nullptr;

std::vector<Bullet> bullets;
std::vector<Bullet> bossBullets;
std::vector<Bullet> enemiesFireBullets;
std::vector<Enemy> enemies;
std::vector<EnemyFire> enemiesFire;
std::vector<Upgrade> upgrades;

void setTexture(){
    backgroundTexture = loadTexture("image/space.png", renderer);
    menuTexture = loadTexture("image/menu.png", renderer);
    bulletTextures[0] = loadTexture("image/bullet0.png", renderer);
    bulletTextures[2] = loadTexture("image/bullet1.png", renderer);
    bulletTextures[3] = loadTexture("image/bullet2.png", renderer);
    bulletTextures[4] = loadTexture("image/bullet3.png", renderer);
    bulletTextures[1] = loadTexture("image/bullet4.png", renderer);
    currentBulletTexture = bulletTextures[0];
    playerTexture = loadTexture("image/pngegg.png", renderer);
    upgradeTexture = loadTexture("image/upgrade.png",renderer);
    enemiesTexture = loadTexture("image/enemis.png",renderer);
    enemiesFireTexture = loadTexture("image/enemisFire.png", renderer);
    enemiesFireBulletTexture = loadTexture("image/enemiesFireBullet.png", renderer);
    bossTexture[0] = loadTexture("image/boss.png",renderer);
    bossTexture[1] = loadTexture("image/boss2.png",renderer);
    bossTexture[2] = loadTexture("image/boss3.png",renderer);
    currentBossTexture = bossTexture[0];
    bossBulletTexture = loadTexture("image/bossbullet.png",renderer);
    soundEffect = Mix_LoadWAV("sounds/fire.WAV");
    boomEffect = Mix_LoadWAV("sounds/boom.WAV");
    dieEffect = Mix_LoadWAV("sounds/die.wav");
    bossDieEffect = Mix_LoadWAV("sounds/explosion.wav");
    upgradeEffect = Mix_LoadWAV("sounds/upgrade.wav");
    bgMusic = Mix_LoadMUS("sounds/music.mp3");
    Mix_PlayMusic(bgMusic, -1);
}

void startGame(){
    currentBulletTexture = loadTexture("image/bullet0.png", renderer);
    bullets.clear();
    enemies.clear();
    upgrades.clear();
    bossBullets.clear();
    enemiesFire.clear();
    enemiesFireBullets.clear();
    boss = nullptr;
    score = 0;
    frameCount = 0;
    bossCount = 0;
    PLAYER_SPEED = 5;
    BULLET_SPEED = 8;
    BULLET_SIZE = 10;
    BULLET_QUANTITY = 1;
    BULLET_POWER = 2;
    ENEMY_SPEED = 3;
    ENEMY_SPAWN_RATE = 50;
    ENEMYFIRE_SPAWN_RATE = 50;
    ENEMY_HEALTH = 5;
    BOSS_HEALTH = 400;
    BOSS_SPEED = 2;
    BOSS_BULLET_SPEED = 7;
    BOSS_BULLET_SIZE = 20;
    upgradeCount = 0;
    nextUpgradeLevel = 2;
    bgY1 = 0;
    bgY2 = -SCREEN_HEIGHT;
}

