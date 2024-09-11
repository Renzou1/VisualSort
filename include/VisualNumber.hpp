#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Globals.hpp"

class VisualNumber
{
public:
    VisualNumber();
    VisualNumber(int val, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr);
    int increment();
    int getVal();
    bool shouldSkipRender();
    void setSkipRender(bool skipRender);
    bool isComparing();
    void setComparing(bool param);
    SDL_Texture* getTexture();
    void destroy();
    void operator=(const VisualNumber& V);
private:
    int val;
    bool skipRender;
    bool isComparing_;
    int isComparingFlag2_;
    SDL_Texture* number_texture;
};