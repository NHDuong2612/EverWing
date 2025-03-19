#include "information.h"
#include "loadTexture.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); // Khởi tạo cả AUDIO
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    SDL_Window* window = SDL_CreateWindow("EverWing SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* backgroundTexture = loadTexture("image/space.png", renderer);
    SDL_Texture* menuTexture = loadTexture("image/menu.png", renderer);
    bulletTextures[0] = loadTexture("image/bullet1.png", renderer);
    bulletTextures[1] = loadTexture("image/bullet2.png", renderer);
    bulletTextures[2] = loadTexture("image/bullet3.png", renderer);
    bulletTextures[3] = loadTexture("image/bullet4.png", renderer);
    currentBulletTexture = bulletTextures[0];
    playerTexture = loadTexture("image/pngegg.png", renderer);
    upgradeTexture = loadTexture("image/upgrade.png",renderer);
    enemiesTexture = loadTexture("image/enemis.png",renderer);
    bossTexture[0] = loadTexture("image/boss.png",renderer);
    bossTexture[1] = loadTexture("image/boss2.png",renderer);
    bossTexture[2] = loadTexture("image/boss3.png",renderer);
    bossBulletTexture = loadTexture("image/bossbullet.png",renderer);
    Mix_Chunk* soundEffect = Mix_LoadWAV("sounds/fire.WAV");
    Mix_Chunk* boomEffect = Mix_LoadWAV("sounds/boom.WAV");
    Mix_Chunk* dieEffect = Mix_LoadWAV("sounds/die.wav");
    Mix_Chunk* bossDieEffect = Mix_LoadWAV("sounds/explosion.wav");
    srand(time(0));
    int playerX = SCREEN_WIDTH / 2 - 25;
    int playerY = SCREEN_HEIGHT - 80;
    int score = 0;
    int frameCount = 0;
    int bossCount = 0;
    bool canShoot = true;
    bool running = false;
    bool menu = true;
    Mix_Music* bgMusic = Mix_LoadMUS("sounds/music.mp3");
    Mix_PlayMusic(bgMusic, -1);  // Phát lặp vô hạn
    Mix_VolumeMusic(60);
    SDL_Event e;
    SDL_Event event;
    while (menu){
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) menu = false;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
        // Giả sử nút Play có vị trí và kích thước sau
                SDL_Rect playButton = {300, 300, 200,50};

                if (e.button.x >= playButton.x && e.button.x <= playButton.x + playButton.w &&
                    e.button.y >= playButton.y && e.button.y <= playButton.y + playButton.h) {
                    running=true;
                }
            }
        }
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    menu=false;
                    running=false;
                }
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.scancode == SDL_SCANCODE_SPACE && canShoot) {
                        Mix_PlayChannel(-1, soundEffect, 0);
                        int spacing = BULLET_SIZE + 5;  // Khoảng cách giữa các viên đạn
                        int totalWidth = BULLET_QUANTITY * spacing - spacing; // Tổng chiều rộng của cả hàng đạn
                        int startX = playerX + (70 / 2) - (totalWidth / 2) - (BULLET_SIZE / 2);

                        for (int i = 0; i < BULLET_QUANTITY; i++) {
                            bullets.push_back({startX + i * spacing, playerY, BULLET_QUANTITY});
                        }
                        canShoot = false;
                    }
                }
                if (event.type == SDL_KEYUP) {
                    if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                        canShoot = true;
                    }
                }
            }

            const Uint8* keys = SDL_GetKeyboardState(NULL);
            if (keys[SDL_SCANCODE_LEFT] && playerX > 0) playerX -= PLAYER_SPEED;
            if (keys[SDL_SCANCODE_RIGHT] && playerX < SCREEN_WIDTH - 70) playerX += PLAYER_SPEED;
            if (keys[SDL_SCANCODE_UP] && playerY > 0) playerY -= PLAYER_SPEED;
            if (keys[SDL_SCANCODE_DOWN] && playerY < SCREEN_HEIGHT - 70) playerY += PLAYER_SPEED;

            for (auto& bullet : bullets) bullet.y -= BULLET_SPEED;
            bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) { return b.y < 0; }), bullets.end());

            if (frameCount % ENEMY_SPAWN_RATE == 0) {
                enemies.push_back({rand() % (SCREEN_WIDTH - 50), 0, ENEMY_HEALTH});
            }

            for (auto& enemy : enemies) enemy.y += ENEMY_SPEED;

            for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
                bool hit = false;
                for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
                    if (bulletIt->x < enemyIt->x + 50 && bulletIt->x + BULLET_SIZE > enemyIt->x &&
                        bulletIt->y < enemyIt->y + 30 && bulletIt->y + BULLET_SIZE > enemyIt->y) {
                        enemyIt->health -=BULLET_POWER ; // Giảm máu theo sức mạnh của viên đạn
                        bulletIt = bullets.erase(bulletIt);
                        if (enemyIt->health <= 0) {
                            Mix_PlayChannel(-1, boomEffect, 0);
                            if (rand() % 100 < UPGRADE_DROP_CHANCE) {
                                upgrades.push_back({enemyIt->x + 20, enemyIt->y + 20});
                            }
                            enemyIt = enemies.erase(enemyIt);
                            score += 10;
                            if (score % 150 == 0) {
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


            for (auto it = upgrades.begin(); it != upgrades.end();) {
                it->y += 2;

                if (playerX < it->x + 20 && playerX + 45 > it->x && playerY < it->y + 20 && playerY + 45 > it->y) {
                    PLAYER_SPEED = std::min(PLAYER_SPEED + 1, 10);
                    BULLET_POWER++;
                    BULLET_SIZE =std::min(BULLET_SIZE+1,25);

                    upgradeCount++;
                    if (upgradeCount >= nextUpgradeLevel) {
                        if (BULLET_QUANTITY < 5) {
                            BULLET_QUANTITY++;
                        }
                        nextUpgradeLevel+=upgradeCount;
                        upgradeCount = 0;
                    }
                    currentBulletTexture = bulletTextures[(int)std::log2(nextUpgradeLevel)-1];
                    it = upgrades.erase(it);
                } else if (it->y > SCREEN_HEIGHT) {
                    it = upgrades.erase(it);
                } else {
                    ++it;
                }
            }

            for (const auto& enemy : enemies) {
                if (playerX + 15 < enemy.x + 50 && playerX + 55 > enemy.x &&
                    playerY < enemy.y + 25 && playerY + 45 > enemy.y) {
                    Mix_PlayChannel(-1, dieEffect, 0);
                    SDL_Delay(100);
                    running = false;
                }
            }
            bgY1 += 1;  // Điều chỉnh tốc độ trượt
            bgY2 += 1;
            if (bgY1 >= SCREEN_HEIGHT) bgY1 = -SCREEN_HEIGHT;
            if (bgY2 >= SCREEN_HEIGHT) bgY2 = -SCREEN_HEIGHT;
            SDL_Rect bgRect1 = {0, bgY1, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_Rect bgRect2 = {0, bgY2, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect1);
            SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect2);
            SDL_Rect playerRect = {playerX, playerY, 70, 70};
            SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

            for (const auto& enemy : enemies) {
                SDL_Rect e = {enemy.x, enemy.y, 50, 50 };
                SDL_RenderCopy(renderer, enemiesTexture, NULL, &e);
            }
            if (score % 500 == 0 && score >0 && boss == nullptr ) {
                currentBossTexture=bossTexture[bossCount];
                bossCount++;
                int newBossHealth = BOSS_HEALTH + bossCount * 200;  // Tăng máu theo số lần xuất hiện
                int newBossSpeed = BOSS_SPEED + bossCount;      // Tăng tốc độ boss
                int newBossBulletSpeed = BOSS_BULLET_SPEED + bossCount ; // Tăng tốc độ đạn
                int newBossBuleetSize = BOSS_BULLET_SIZE *2;
                boss = new Boss{SCREEN_WIDTH / 2 - 50, 50, newBossHealth, true};

            // Cập nhật thông số
                BOSS_HEALTH = newBossHealth;
                BOSS_SPEED = newBossSpeed; // Giới hạn tốc độ tối đa
                BOSS_BULLET_SPEED = newBossBulletSpeed;
                BOSS_BULLET_SIZE = newBossBuleetSize;
            }
            if (boss) {
                if (boss->movingRight) {
                    boss->x += BOSS_SPEED;
                    if (boss->x + 100 >= SCREEN_WIDTH) boss->movingRight = false;
                } else {
                    boss->x -= BOSS_SPEED;
                    if (boss->x <= 0) boss->movingRight = true;
                }
                if (frameCount % 80 == 0) {
                    bossBullets.push_back({boss->x + 50, boss->y + 100});
                }
            }
            for (auto it = bossBullets.begin(); it != bossBullets.end();) {
                it->y += BOSS_BULLET_SPEED;

                if (boss && it->x < playerX + 45 && it->x + BOSS_BULLET_SIZE > playerX &&
                it->y < playerY + 45 && it->y + BOSS_BULLET_SIZE > playerY) {
                    running = false; // Game kết thúc
                }
                if (it->y > SCREEN_HEIGHT) {
                    it = bossBullets.erase(it);
                } else {
                    ++it;
                }
            }

            if (boss) {
                for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
                    if (bulletIt->x < boss->x + 100 && bulletIt->x + BULLET_SIZE > boss->x &&
                        bulletIt->y < boss->y + 100 && bulletIt->y + BULLET_SIZE > boss->y) {

                        boss->health -= BULLET_POWER;
                        bulletIt = bullets.erase(bulletIt);

                        if (boss->health <= 0) {
                            Mix_PlayChannel (-1, bossDieEffect, 0);
                            delete boss;
                            boss = nullptr;
                            score += 100;
                            break;

                        }
                    } else {
                        ++bulletIt;
                    }
                }
            }

            for (const auto& bossBullet : bossBullets) {
                SDL_Rect b = {bossBullet.x, bossBullet.y, BOSS_BULLET_SIZE, BOSS_BULLET_SIZE};
                SDL_RenderCopy(renderer, bossBulletTexture, NULL, &b);
            }

            for (const auto& bullet : bullets) {
                SDL_Rect b = {bullet.x, bullet.y, BULLET_SIZE, 3 * BULLET_SIZE};
                SDL_RenderCopy(renderer, currentBulletTexture, NULL, &b);
            }
            for (const auto& upgrade : upgrades) {
                SDL_Rect u = {upgrade.x, upgrade.y, 20, 20};
                SDL_RenderCopy(renderer,upgradeTexture,NULL ,&u);
            }
            if (boss!=nullptr) {
                SDL_Rect bossRect = {boss->x, boss->y, 120, 120};
                SDL_RenderCopy(renderer,currentBossTexture,NULL, &bossRect);
            }

            renderScore(renderer, score);
            frameCount++;
            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
        currentBulletTexture = loadTexture("image/bullet1.png", renderer);
        bullets.clear();
        enemies.clear();
        upgrades.clear();
        bossBullets.clear();
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
        ENEMY_HEALTH = 5;
        BOSS_HEALTH = 400;
        BOSS_SPEED = 2;
        BOSS_BULLET_SPEED = 7;
        BOSS_BULLET_SIZE = 20;
        upgradeCount = 0;
        nextUpgradeLevel = 2;
        bgY1 = 0;
        bgY2 = -SCREEN_HEIGHT;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(menuTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(currentBulletTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(enemiesTexture);
    SDL_DestroyTexture(upgradeTexture);
    SDL_DestroyTexture(bossBulletTexture);
    for (int i = 0; i < 3; i++) {
        SDL_DestroyTexture(bossTexture[i]);
    }
    for (int i = 0; i < 4; i++) {
        SDL_DestroyTexture(bulletTextures[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_HaltMusic();  // Dừng nhạc nền
    Mix_FreeMusic(bgMusic);
    Mix_FreeChunk(soundEffect);
    Mix_FreeChunk(boomEffect);
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}
