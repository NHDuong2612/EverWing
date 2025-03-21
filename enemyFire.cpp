#include "enemyFire.h"
#include "information.h"
#include "loadTexture.h"
#include <SDL_mixer.h>
#include <algorithm>

void enemyshoot(std::vector<Bullet>& enemiesFireBullets) {
    if (!enemiesFire.empty() && frameCount % 120 == 0) {
        enemiesFireBullets.push_back({enemiesFire.back().x + 20, enemiesFire.back().y + 20});
    }
}
void spawnEnemyFire(std::vector<EnemyFire>& enemiesFire) {
    if (rand() % 100 == 0) {
        enemiesFire.push_back({rand() % (SCREEN_WIDTH - 50), 0, ENEMY_HEALTH});
    }
}

void updateEnemiesFire(std::vector<EnemyFire>& enemiesFire, std::vector<Bullet>& bullets, int playerX,  int playerY, bool& running, int& score, std::vector<Upgrade>& upgrades) {
    for (auto& enemy : enemiesFire) {
        enemy.y += ENEMY_SPEED;

        if (enemy.x < playerX + 40 && enemy.x + 40 > playerX &&
            enemy.y < playerY + 50 && enemy.y + 45 > playerY) {
            Mix_PlayChannel(-1, dieEffect, 0);
            SDL_Delay(100);
            running = false;
            return;
        }
    }

    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool hit = false;
        for (auto enemyIt = enemiesFire.begin(); enemyIt != enemiesFire.end();) {
            if (bulletIt->x < enemyIt->x + 50 && bulletIt->x + BULLET_SIZE > enemyIt->x &&
                bulletIt->y < enemyIt->y + 20 && bulletIt->y + BULLET_SIZE > enemyIt->y) {
                enemyIt->health -= BULLET_POWER;
                bulletIt = bullets.erase(bulletIt);
                if (enemyIt->health <= 0) {
                    Mix_PlayChannel(-1, boomEffect,0);
                    if (rand() % 100 < UPGRADE_DROP_CHANCE) {
                        upgrades.push_back({enemyIt->x + 20, enemyIt->y + 20});
                    }
                    score += 10;
                    if (score % 200 == 0) {
                        ENEMY_HEALTH+=ENEMY_HEALTH;
                        ENEMY_SPEED = std::min(10, ENEMY_SPEED + 1);
                        ENEMY_SPAWN_RATE = std::max(40, ENEMY_SPAWN_RATE-5);
                    }
                    enemyIt = enemiesFire.erase(enemyIt);
                }
                hit = true;
                break;
            } else {
                ++enemyIt;
            }
        }
        if (!hit) ++bulletIt;
    }
}

void renderEnemiesFire(SDL_Renderer* renderer, SDL_Texture* enemyFireTexture, const std::vector<EnemyFire>& enemiesFire) {
    for (const auto& enemyFire : enemiesFire) {
        SDL_Rect e = {enemyFire.x, enemyFire.y, 50, 50};
        SDL_RenderCopy(renderer, enemyFireTexture, NULL, &e);
    }
}

void updateEnemiesFireBullets(std::vector<Bullet>& enemiesFireBullets, int playerX, int playerY, bool& running) {
    for (auto it = enemiesFireBullets.begin(); it != enemiesFireBullets.end();) {
        it->y += ENEMY_BULLET_SPEED;

        if (it->x < playerX + 50 && it->x + ENEMY_BULLET_SIZE -10 > playerX &&
            it->y < playerY + 45 && it->y + ENEMY_BULLET_SIZE -10 > playerY) {
            running = false;
        }

        if (it->y > SCREEN_HEIGHT) {
            it = enemiesFireBullets.erase(it);
        } else {
            ++it;
        }
    }
}
void renderenemiesFireBullets(SDL_Renderer* renderer, SDL_Texture* bulletTexture, std::vector<Bullet>& enemiesFireBullets) {
    for (const auto& bullet : enemiesFireBullets) {
        SDL_Rect bulletRect = {bullet.x, bullet.y, ENEMY_BULLET_SIZE, 2 * ENEMY_BULLET_SIZE};
        SDL_RenderCopy(renderer, bulletTexture, nullptr, &bulletRect);
    }
}


