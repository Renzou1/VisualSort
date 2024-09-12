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
    int getX() {  return x;  };
    int getY(){  return y;  };
    void setX(int x_) {  x = x_;  };
    void setY(int y_) {  y = y_;  };
    SDL_Texture* getTexture();
    void destroy();
    void operator=(const VisualNumber& V);
    void renderCopy(unsigned int* time_counter,
                              SDL_Rect* number_rect_ptr,
                              SDL_Texture* red_square_texture_ptr,
                              SDL_Renderer* renderer_ptr);
private:
    int value;
    int x;
    int y;
    bool skipRender;
    bool isComparing;
    SDL_Texture* texture;
};