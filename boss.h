#pragma once

#ifndef BOSS_H
#define BOSS_H

#include "struct.h"
#include <SDL.h>
#include <vector>
#include "loadTexture.h"
#include "information.h"
#include "boss.h"

void shoot(std::vector<Bullet>& bossBullets);
void updateBossBullets(std::vector<Bullet>& bossBullets, int playerX, int playerY, bool& running);
void spawnBoss(int& score, Boss*& boss, SDL_Texture*& currentBossTexture, int& bossCount);
void updateBoss(Boss*& boss, std::vector<Bullet>& bullets, std::vector<Bullet>& bossBullets, int& score);
void renderBoss(SDL_Renderer* renderer, Boss* boss);
void renderBossBullets(SDL_Renderer* renderer, SDL_Texture* bossBulletTexture, std::vector<Bullet>& bossBullets);

#endif
