#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class VisualNumber
{
public:
    VisualNumber();
    VisualNumber(int val, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr);
    int increment();
    int getVal();
    bool shouldntSkip();
    void skipRender();
    void unskip();
    bool isComparing();
    void setComparing(bool param);
    int getFlag2();
    void incrementFlag2();
    void resetFlag2();
    SDL_Texture* getTexture();
    void destroy();
    void operator=(const VisualNumber& V);
private:
    int val;
    bool dontSkip;
    bool isComparing_;
    int isComparingFlag2_;
    SDL_Texture* number_texture;
};