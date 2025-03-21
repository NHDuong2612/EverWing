#ifndef ENEMYFIRE_H
#define ENEMYFIRE_H

#include "information.h"
#include "struct.h"
#include "loadTexture.h"
#include <vector>

void enemyshoot(std::vector<Bullet>& enemiesFireBullets);
void spawnEnemyFire(std::vector<EnemyFire>& enemiesFire);
void updateEnemiesFire(std::vector<EnemyFire>& enemiesFire, std::vector<Bullet>& enemiesFireBullets, int playerX,int playerY, bool& running, int& score, std::vector<Upgrade>& upgrades);
void renderEnemiesFire(SDL_Renderer* renderer, SDL_Texture* enemyFireTexture, const std::vector<EnemyFire>& enemiesFire);
void updateEnemiesFireBullets(std::vector<Bullet>& enemiesFireBullets, int playerX, int playerY, bool& running);
void renderenemiesFireBullets(SDL_Renderer* renderer, SDL_Texture* bulletTexture, std::vector<Bullet>& enemiesFireBullets);

#endif
