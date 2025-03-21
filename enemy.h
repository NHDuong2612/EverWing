#ifndef ENEMY_H
#define ENEMY_H

#include "struct.h"
#include "loadTexture.h"
#include <vector>
#include "information.h"

void spawnEnemy(std::vector<Enemy>& enemies);
void updateEnemies(std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, int playerX,int playerY, bool& running, int& score, std::vector<Upgrade>& upgrades);
void renderEnemies(SDL_Renderer* renderer, SDL_Texture* enemyTexture, const std::vector<Enemy>& enemies);

#endif
