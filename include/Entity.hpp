#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Entity
{
public:
    Entity(float p_x, float p_y, SDL_Texture* p_tex);
    float getX();
    void xpp();
    float getY();
    SDL_Texture* getTexture();
    SDL_Rect getCurrentFrame();
private:
    float x, y;
    SDL_Rect currentFrame;
    SDL_Texture* texture;
};
