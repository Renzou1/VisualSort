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

    TTF_Font* font_ptr =  TTF_OpenFont("C:/Windows/Fonts/Rubik-Regular.ttf", FONT_SIZE);
    if( font_ptr == NULL )
    {
        std::cout << "Couldn't find font." << std::endl;
    }
    
    int array[SIZE] = {4, 6, 2, 9, 3, 1, 5};
    SDL_Rect initial_rect = makeInitialRect(array, font_ptr);
    VisualArray visualArray(array, SIZE, 2, &initial_rect, renderer_ptr, font_ptr);
    visualArray.addPointer(false, 0, font_ptr, "i");
    visualArray.addPointer(true, 0, font_ptr, "j");

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

    destroyVisualSort(window_ptr, font_ptr, &visualArray);
    return 0;
}