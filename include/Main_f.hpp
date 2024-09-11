#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Globals.hpp"
#include "VisualArray.hpp"

const int getDoubleDigitWidth(TTF_Font* font_ptr){
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font_ptr, "10", {255, 255, 255});
    const int double_digit_width = temp_surface->w;
    SDL_FreeSurface (temp_surface);
    return double_digit_width;
}

TTF_Font* initializeFont(const int font_size){
    if(TTF_Init() != 0)
    {
        std::cout << "TTF_init has failed. Error: " << TTF_GetError() << std::endl;
    }

    TTF_Font* font_ptr =  TTF_OpenFont("Rubik-Regular.ttf", font_size);
    if( font_ptr == NULL )
    {
        std::cout << "Couldn't find font." << std::endl;
    }    

    return font_ptr;
}

SDL_Window* initializeVisualSort(const int size, const int double_digit_width, const int algorithm)
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "Hey.. SDL_Init HAS FAILED: SDL_ERROR " << SDL_GetError() << std::endl;
    }

    if(!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
    }
    
    // should be RED_SQUARE_WIDTH + RED_SQUARE_WIDTH * size + RED_SQUARE_WIDTH
    const int window_width =  RED_SQUARE_WIDTH/2 + RED_SQUARE_WIDTH * size + RED_SQUARE_WIDTH;
    const int window_height = 600 + RED_SQUARE_WIDTH/2;
    std::string window_name = "VisualSort V0 - ";
    switch(algorithm){
        case SELECTION_SORT:
            window_name += "selection sort";
            break;
        case INSERTION_SORT:
            window_name += "insertion sort";
            break;
        case MERGE_SORT:
            window_name += "merge sort";
            break;
        case QUICK_SORT:
            window_name += "quicksort";
            break;
    }
    SDL_Window* window = SDL_CreateWindow(
        window_name.c_str(), 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        window_width , window_height, 
        SDL_WINDOW_SHOWN
        );

    if(window == NULL)
    {
        std::cout << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
    }

    return window;
}

VisualArray makeVisualArray(const int array[], const int pointersSize, Configuration* config_ptr)
{
    SDL_Surface* temp_surface = TTF_RenderText_Solid(config_ptr->font_ptr, "10", {255, 255, 255});
    SDL_Rect initial_digit_rect;
    const int double_digit_width = temp_surface->w;
    initial_digit_rect.w = double_digit_width;
    initial_digit_rect.h = temp_surface->h;    
    initial_digit_rect.x = RED_SQUARE_WIDTH;
    initial_digit_rect.y = DISTANCE_TO_TOP_OF_SCREEN;
    SDL_FreeSurface (temp_surface);
    int window_height, window_width;
    SDL_GetWindowSize(config_ptr->window_ptr, &window_width, &window_height);

    VisualArray visualArray(array, config_ptr->size, pointersSize, initial_digit_rect, 
    config_ptr->renderer_ptr, config_ptr->font_ptr, config_ptr->font_size, window_height, window_width);
    config_ptr->visualArray_ptr = &visualArray;
    return visualArray;
}

void destroyVisualSort(SDL_Window* window, TTF_Font* font, VisualArray* visualArray)
{
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    visualArray->destroy();
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

void waitForInput(Configuration* config_ptr, const unsigned int delay_before_input)
{
    SDL_RenderClear(config_ptr->renderer_ptr);
    config_ptr->visualArray_ptr->renderArray();
    SDL_RenderPresent(config_ptr->renderer_ptr);
    SDL_Delay(delay_before_input / SPEED);
    if(WAIT_FOR_INPUT == false)
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

void waitToQuit(Configuration* config_ptr)
{
    while(true)
    {
        while(SDL_PollEvent(config_ptr->event_ptr))
        {
            switch(config_ptr->event_ptr->type)
            {
                case SDL_QUIT:
                    destroyVisualSort(config_ptr);  
            }
        }
    }
}