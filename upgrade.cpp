#include "upgrade.h"
#include "information.h"
#include <algorithm>
#include <cmath>

void handleUpgrades(std::vector<Upgrade>& upgrades, int& playerX, int& playerY, int& PLAYER_SPEED, int& BULLET_POWER, int& BULLET_SIZE, int& BULLET_QUANTITY, int& upgradeCount, int& nextUpgradeLevel, SDL_Texture*& currentBulletTexture, SDL_Texture* upgradeTexture, SDL_Renderer* renderer) {
    for (auto it = upgrades.begin(); it != upgrades.end();) {
        it->y += 2;

        if (playerX < it->x + 20 && playerX + 45 > it->x && playerY < it->y + 20 && playerY + 45 > it->y) {
            Mix_PlayChannel(-1, upgradeEffect, 0);
            PLAYER_SPEED = std::min(PLAYER_SPEED + 1, 10);
            BULLET_POWER++;
            BULLET_SIZE = std::min(BULLET_SIZE + 1, 30);
            upgradeCount++;

            if (upgradeCount >= nextUpgradeLevel) {
                if (BULLET_QUANTITY < 5) BULLET_QUANTITY++;
                nextUpgradeLevel += upgradeCount;
                upgradeCount = 0;
                currentBulletTexture = bulletTextures[(int)std::log2(nextUpgradeLevel) - 1];
            }
            it = upgrades.erase(it);
        } else if (it->y > SCREEN_HEIGHT) {
            it = upgrades.erase(it);
        } else {
            SDL_Rect u = {it->x, it->y, 20, 20};
            SDL_RenderCopy(renderer, upgradeTexture, NULL, &u);
            ++it;
        }
    }
}

void renderUpgrade(SDL_Renderer* renderer){
    for (const auto& upgrade : upgrades) {
        SDL_Rect u = {upgrade.x, upgrade.y, 20, 20};
        SDL_RenderCopy(renderer,upgradeTexture,NULL ,&u);
    }
}
