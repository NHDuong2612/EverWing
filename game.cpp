#include "game.h"
#include "quit.h"
void initGame() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    TTF_Init();
    font = TTF_OpenFont("font/font.ttf", 28);
    window = SDL_CreateWindow("EverWing SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    setTexture();
    Mix_PlayMusic(bgMusic, -1);
    Mix_VolumeMusic(80);
    Mix_VolumeChunk(soundEffect, 80);
    Mix_VolumeChunk(upgradeEffect, 400);
    srand(time(0));
}

void gameLoop() {
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                menu = false; // Thoát game hoàn toàn
            }
            playerShoot(event);
        }

        handlePlayerInput(SDL_GetKeyboardState(NULL));
        updatePlayerBullets();
        spawnEnemy(enemies);
        updateEnemies(enemies, bullets, playerX, playerY, running, score, upgrades);
        spawnEnemyFire(enemiesFire);
        updateEnemiesFire(enemiesFire, bullets, playerX, playerY, running, score, upgrades);
        enemyshoot(enemiesFireBullets);
        updateEnemiesFireBullets(enemiesFireBullets, playerX, playerY, running);
        handleUpgrades(upgrades, playerX, playerY, PLAYER_SPEED, BULLET_POWER, BULLET_SIZE, BULLET_QUANTITY, upgradeCount, nextUpgradeLevel, currentBulletTexture, upgradeTexture, renderer);
        bgY1 += 1;
        bgY2 += 1;
        if (bgY1 >= SCREEN_HEIGHT) bgY1 = -SCREEN_HEIGHT;
        if (bgY2 >= SCREEN_HEIGHT) bgY2 = -SCREEN_HEIGHT;
        SDL_Rect bgRect1 = {0, bgY1, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect bgRect2 = {0, bgY2, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect1);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect2);
        renderPlayer(renderer);
        renderEnemiesFire(renderer, enemiesFireTexture, enemiesFire);
        renderEnemies(renderer, enemiesTexture, enemies);
        renderenemiesFireBullets(renderer, enemiesFireBulletTexture, enemiesFireBullets);
        spawnBoss(score, boss, currentBossTexture, bossCount);
        updateBoss(boss, bullets, bossBullets, score);
        updateBossBullets(bossBullets, playerX, playerY, running);
        renderBossBullets(renderer, bossBulletTexture, bossBullets);
        renderUpgrade(renderer);
        renderBoss(renderer, boss);
        renderScore(renderer, score, font);
        frameCount++;
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}


void handleEvents(SDL_Event& event, bool& running) {
    if (event.type == SDL_QUIT) {
        running = false;
    }
    playerShoot(event);
}

void updateGame() {
    handlePlayerInput(SDL_GetKeyboardState(NULL));
    updatePlayerBullets();
    spawnEnemy(enemies);
    updateEnemies(enemies, bullets, playerX, playerY, running, score, upgrades);
    spawnEnemyFire(enemiesFire);
    updateEnemiesFire(enemiesFire, bullets, playerX, playerY, running, score, upgrades);
    enemyshoot(enemiesFireBullets);
    updateEnemiesFireBullets(enemiesFireBullets, playerX, playerY, running);
    handleUpgrades(upgrades, playerX, playerY, PLAYER_SPEED, BULLET_POWER, BULLET_SIZE, BULLET_QUANTITY, upgradeCount, nextUpgradeLevel, currentBulletTexture, upgradeTexture, renderer);
    spawnBoss(score, boss, currentBossTexture, bossCount);
    updateBoss(boss, bullets, bossBullets, score);
    updateBossBullets(bossBullets, playerX, playerY, running);
}

void renderGame() {
    bgY1 += 1;
    bgY2 += 1;
    if (bgY1 >= SCREEN_HEIGHT) bgY1 = -SCREEN_HEIGHT;
    if (bgY2 >= SCREEN_HEIGHT) bgY2 = -SCREEN_HEIGHT;

    SDL_Rect bgRect1 = {0, bgY1, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect bgRect2 = {0, bgY2, SCREEN_WIDTH, SCREEN_HEIGHT};

    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect1);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect2);
    renderPlayer(renderer);
    renderEnemiesFire(renderer, enemiesFireTexture, enemiesFire);
    renderEnemies(renderer, enemiesTexture, enemies);
    renderenemiesFireBullets(renderer, enemiesFireBulletTexture, enemiesFireBullets);
    renderBossBullets(renderer, bossBulletTexture, bossBullets);
    renderBoss(renderer, boss);
    renderScore(renderer, score, font);
    renderUpgrade(renderer);
    SDL_RenderPresent(renderer);
}

void cleanupGame() {
    quit();
}

