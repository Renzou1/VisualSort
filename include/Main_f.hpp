#pragma once

#include <SDL2/SDL.h>
#include "Globals.hpp"
#include "VisualArray.hpp"

SDL_Window* initializeVisualSort(int size, int font_size)
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "Hey.. SDL_Init HAS FAILED: SDL_ERROR " << SDL_GetError() << std::endl;
    }

    if(!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
    }

    if(TTF_Init() != 0)
    {
        std::cout << "TTF_init has failed. Error: " << TTF_GetError() << std::endl;
    }

    const int window_width = font_size * 2 * size + 200;
    const int window_height = 600;
    SDL_Window* window = SDL_CreateWindow(
        "VisualSort V0", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        window_width , window_height, 
        SDL_WINDOW_SHOWN
        );

    if(window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    return window;
}

VisualArray makeVisualArray(int array[], int pointers, Configuration* config_ptr )
{
    SDL_Surface* temp_surface = TTF_RenderText_Solid(config_ptr->font_ptr, std::to_string(array[0]).c_str(), {255, 255, 255});
    SDL_Rect initial_rect;
    initial_rect.x = config_ptr->DISTANCE;
    initial_rect.y = 250;
    initial_rect.w = temp_surface->w;
    initial_rect.h = temp_surface->h;
    SDL_FreeSurface (temp_surface);

    VisualArray visualArray(array, config_ptr->size, pointers, initial_rect, 
    config_ptr->renderer_ptr, config_ptr->font_ptr, config_ptr->font_size);
    config_ptr->visualArray_ptr = &visualArray;
    return visualArray;
}

void destroyVisualSort(SDL_Window* window, TTF_Font* font, VisualArray* visualArray)
{
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    (*visualArray).destroy();
    TTF_Quit();
    SDL_Quit();
    std::exit(0);
}

void destroyVisualSort(Configuration* config)
{
    SDL_DestroyWindow(config->window_ptr);
    TTF_CloseFont(config->font_ptr);
    config->visualArray_ptr->destroy();
    TTF_Quit();
    SDL_Quit();
    std::exit(0);
}

void waitForInput(Configuration* config_ptr)
{
    if(NO_WAITING == 1)
    {  return;  }
    while(true)
    {
        while(SDL_PollEvent(config_ptr->event_ptr))
        {
            switch(config_ptr->event_ptr->type)
            {
                case SDL_QUIT:
                    destroyVisualSort(config_ptr);  
                case SDL_KEYDOWN:
                    return;  
            }
        }
        SDL_RenderClear(config_ptr->renderer_ptr);
        config_ptr->visualArray_ptr->renderArray();
        SDL_RenderPresent(config_ptr->renderer_ptr);
    }
}

