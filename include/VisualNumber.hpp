#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class VisualNumber
{
public:
    VisualNumber();
    VisualNumber(int val, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
    int increment();
    int getVal();
    SDL_Texture* getTexture();
private:
    int val;
    SDL_Texture* number_texture;
};