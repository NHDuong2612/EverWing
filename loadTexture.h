#include<SDL.h>
#include<SDL_image.h>

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
void renderScore(SDL_Renderer* renderer, int score);
void handleMenuEvents(SDL_Event& e);
