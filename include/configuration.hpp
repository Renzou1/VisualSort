#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct Configuration
{
    SDL_Renderer* renderer_ptr;
    SDL_Event* event_ptr;
    TTF_Font* font_ptr;
    SDL_Window* window_ptr;
    const short size;
    const unsigned short font_size;
} Configuration;