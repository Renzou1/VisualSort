#pragma once

#include <Globals.hpp>
#include <VisualArray.hpp>

SDL_Window* initializeVisualSort()
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

    
    SDL_Window* window = SDL_CreateWindow(
        "VisualSort V0", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        WINDOW_WIDTH , WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN
        );

    if(window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    return window;
}

void destroyVisualSort(SDL_Window* window, TTF_Font* font, VisualArray* visualArray)
{
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    (*visualArray).destroy();
    TTF_Quit();
    SDL_Quit();
}