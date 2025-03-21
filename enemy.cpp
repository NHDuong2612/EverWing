#include "enemy.h"
#include <cstdlib>
#include "information.h"
void spawnEnemy(std::vector<Enemy>& enemies) {
    if (rand() % 100 == 0) {
        enemies.push_back({rand() % (SCREEN_WIDTH - 50), 0, ENEMY_HEALTH});
    }
}

void updateEnemies(std::vector<Enemy>& enemies, std::vector<Bullet>& bullets, int playerX,  int playerY, bool& running, int& score, std::vector<Upgrade>& upgrades) {
    for (auto& enemy : enemies) {
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
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            if (bulletIt->x < enemyIt->x + 50 && bulletIt->x + BULLET_SIZE > enemyIt->x &&
                bulletIt->y < enemyIt->y + 25 && bulletIt->y + BULLET_SIZE > enemyIt->y) {
                enemyIt->health -= BULLET_POWER;
                bulletIt = bullets.erase(bulletIt);
                if (enemyIt->health <= 0) {
                    Mix_PlayChannel(-1, boomEffect, 0);
                    if (rand() % 100 < UPGRADE_DROP_CHANCE) {
                        upgrades.push_back({enemyIt->x + 20, enemyIt->y + 20});
                    }
                    enemyIt = enemies.erase(enemyIt);
                    score += 10;
                    if (score % 200 == 0) {
                        ENEMY_HEALTH+=ENEMY_HEALTH;
                        ENEMY_SPEED = std::min(10, ENEMY_SPEED + 1);
                        ENEMY_SPAWN_RATE = std::max(40, ENEMY_SPAWN_RATE-5);
                    }
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

void renderEnemies(SDL_Renderer* renderer, SDL_Texture* enemyTexture, const std::vector<Enemy>& enemies) {
    for (const auto& enemy : enemies) {
        SDL_Rect e = {enemy.x, enemy.y, 50, 50};
        SDL_RenderCopy(renderer, enemyTexture, NULL, &e);
    }
}
