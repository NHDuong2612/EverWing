#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include "information.h"
#include "struct.h"

void handlePlayerInput(const Uint8* keys);
void playerShoot(SDL_Event& event);
void updatePlayerBullets();
void renderPlayer(SDL_Renderer* renderer);

#endif

