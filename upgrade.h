#ifndef UPGRADE_H
#define UPGRADE_H

#include <vector>
#include "SDL.h"
#include "struct.h"

void handleUpgrades(std::vector<Upgrade>& upgrades, int& playerX, int& playerY, int& PLAYER_SPEED, int& BULLET_POWER, int& BULLET_SIZE, int& BULLET_QUANTITY, int& upgradeCount, int& nextUpgradeLevel, SDL_Texture*& currentBulletTexture, SDL_Texture* upgradeTexture, SDL_Renderer* renderer);
void renderUpgrade(SDL_Renderer* renderer);
#endif

