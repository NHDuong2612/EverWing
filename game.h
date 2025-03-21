#ifndef GAME_H
#define GAME_H

#include "information.h"
#include "player.h"
#include "enemy.h"
#include "boss.h"
#include "upgrade.h"
#include "enemyFire.h"
#include "SDL_ttf.h"

void initGame();
void gameLoop();
void handleEvents(SDL_Event& event, bool& running);
void updateGame();
void renderGame();
void cleanupGame();

#endif

