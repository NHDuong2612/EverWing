#include "boss.h"
#include "information.h"
#include "loadTexture.h"
#include <SDL_mixer.h>
#include <algorithm>

extern Mix_Chunk* bossDieEffect;
extern SDL_Texture* bossTexture[];
extern SDL_Texture* bossBulletTexture;

void Boss::move() {
    if (movingRight) {
        x += BOSS_SPEED;
        if (x + 100 >= SCREEN_WIDTH) movingRight = false;
    } else {
        x -= BOSS_SPEED;
        if (x <= 0) movingRight = true;
    }
}

void shoot(std::vector<Bullet>& bullets) {
    if (frameCount % 80 == 0) {
        bossBullets.push_back({boss->x + 50, boss->y + 100});
    }
}


void spawnBoss(int& score, Boss*& boss, SDL_Texture*& currentBossTexture, int& bossCount) {
    if (score % 500 == 0 && score > 0 && boss == nullptr) {
        currentBossTexture = bossTexture[bossCount%3];
        bossCount++;
        int newBossHealth = BOSS_HEALTH + bossCount * 500;
        boss = new Boss(SCREEN_WIDTH / 2 - 50, 50, newBossHealth);
        BOSS_HEALTH = newBossHealth;
        BOSS_SPEED += bossCount;
        BOSS_BULLET_SPEED += bossCount;
        BOSS_BULLET_SIZE *= 2;
    }
}

void updateBoss(Boss*& boss, std::vector<Bullet>& bullets, std::vector<Bullet>& bossBullets, int& score) {
    if (!boss) return;
    boss->move();
    if (frameCount % 80 == 0) {
        shoot(bossBullets);
    }

    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        if (bulletIt->x < boss->x + 100 && bulletIt->x + BULLET_SIZE > boss->x &&
            bulletIt->y < boss->y + 100 && bulletIt->y + BULLET_SIZE > boss->y) {
            boss->health -= BULLET_POWER;
            bulletIt = bullets.erase(bulletIt);
            if (boss->health <= 0) {
                Mix_PlayChannel(-1, bossDieEffect, 0);
                delete boss;
                boss = nullptr;
                score += 100;
                bossCount++;
                break;
            }
        } else {
            ++bulletIt;
        }
    }
}

void renderBoss(SDL_Renderer* renderer, Boss* boss) {
    if (!boss) return;
    SDL_Rect bossRect = {boss->x, boss->y, 120, 120};
    SDL_RenderCopy(renderer, currentBossTexture, NULL, &bossRect);
}

void updateBossBullets(std::vector<Bullet>& bossBullets, int playerX, int playerY, bool& running) {
    for (auto it = bossBullets.begin(); it != bossBullets.end();) {
        it->y += BOSS_BULLET_SPEED;

        if (it->x < playerX + 45 && it->x + BOSS_BULLET_SIZE > playerX &&
            it->y < playerY + 45 && it->y + BOSS_BULLET_SIZE > playerY) {
            running = false;
        }

        if (it->y > SCREEN_HEIGHT) {
            it = bossBullets.erase(it);
        } else {
            ++it;
        }
    }
}
void renderBossBullets(SDL_Renderer* renderer, SDL_Texture* bulletTexture, std::vector<Bullet>& bossBullets) {
    for (const auto& bullet : bossBullets) {
        SDL_Rect bulletRect = {bullet.x, bullet.y, BOSS_BULLET_SIZE, 2 * BOSS_BULLET_SIZE};
        SDL_RenderCopy(renderer, bossBulletTexture, nullptr, &bulletRect);
    }
}

