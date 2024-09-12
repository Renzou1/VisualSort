#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Globals.hpp"

class VisualNumber
{
public:
    VisualNumber();
    VisualNumber(int value, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr);
    int increment();
    int getValue();
    bool shouldSkipRender();
    void setSkipRender(bool skipRender);
    bool getIsComparing();
    void setComparing(bool param);
    SDL_Texture* getTexture();
    void destroy();
    void operator=(const VisualNumber& V);
    void renderCopy(const int single_digit_width, 
                                  const int double_digit_width,
                                  unsigned int* time_counter,
                                  SDL_Rect* number_rect_ptr,
                                  SDL_Rect* red_square_rect_ptr,
                                  SDL_Texture* red_square_texture_ptr,
                                  SDL_Renderer* renderer_ptr);
private:
    int value;
    bool skipRender;
    bool isComparing;
    SDL_Texture* texture;
};