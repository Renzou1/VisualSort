#pragma once

#include <Globals.hpp>
#include <SDL2/SDL_ttf.h>

unsigned int SINGLE_DIGIT_WIDTH;
unsigned int DOUBLE_DIGIT_WIDTH;
unsigned int TEXT_HEIGHT;

void setGlobalTextDimensions(TTF_Font* font_ptr)
{
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font_ptr, "0", WHITE);
    SINGLE_DIGIT_WIDTH = temp_surface->w;
    TEXT_HEIGHT = temp_surface->h;
    SDL_FreeSurface(temp_surface);     

    temp_surface = TTF_RenderText_Solid(font_ptr, "10", {255, 255, 255});
    DOUBLE_DIGIT_WIDTH = temp_surface->w;
    SDL_FreeSurface (temp_surface);     
}