#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
void handleMenuEvents(SDL_Event& e);
void renderScore(SDL_Renderer* renderer, int score, TTF_Font* font);
