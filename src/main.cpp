#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

#include "Globals.hpp"
#include "Main_f.hpp"
#include "VisualArray.hpp"
#include "VisualNumber.hpp"

// g++ -I include -L lib -o main src/* -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf  -Wall

int main ( int argc, char *argv[] )
{

    SDL_Window* window_ptr = initializeVisualSort();
    SDL_Renderer* renderer_ptr = SDL_CreateRenderer(window_ptr, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* arrow_texture_ptr = IMG_LoadTexture(renderer_ptr, "resources/arrow.png");

    TTF_Font* arial =  TTF_OpenFont("Arial.ttf", FONT_SIZE);
    if( arial == NULL )
    {
        std::cout << "Couldn't find font." << std::endl;
    }
    
    SDL_Rect initial_rect;
    initial_rect.x = 100;
    initial_rect.y = 400;
    initial_rect.w = NUMBER_SIZE;
    initial_rect.h = NUMBER_SIZE * 1.2;

    int array[SIZE] = {4, 6, 10, 12, 3};
    VisualArray visualArray(array, SIZE, 2, &initial_rect, renderer_ptr, arial);
    visualArray.addPointer(true, 0, arial, "L");

    bool running = true;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        SDL_RenderClear(renderer_ptr);
        visualArray.renderArray();
        SDL_RenderPresent(renderer_ptr);
        SDL_Delay(10);
    }

    destroyVisualSort(window_ptr, arial, &visualArray);
    return 0;
}