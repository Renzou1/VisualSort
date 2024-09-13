#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Globals.hpp"
#include "configuration.hpp"

class VisualNumber
{
public:
    VisualNumber();
    VisualNumber(int value, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr);
    int increment();
    int getValue();
    void setValue(const int value_, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr);
    bool shouldSkipRender();
    void setSkipRender(bool skipRender);
    bool getIsComparing();
    void setComparing(bool param);
    short getX() {  return x;  };
    short getY(){  return y;  };
    void setX(short x_) {  x = x_;  };
    void setY(short y_) {  y = y_;  };
    SDL_Texture* getTexture();
    void destroy();
    void operator=(const VisualNumber& V);
    void renderCopy(unsigned short* time_counter,
                              SDL_Rect* number_rect_ptr,
                              SDL_Texture* red_square_texture_ptr,
                              SDL_Renderer* renderer_ptr);
private:
    int value;
    short x;
    short y;
    bool skipRender;
    bool isComparing;
    SDL_Texture* texture;
};