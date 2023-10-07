#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "VisualNumber.hpp"
#include "VisualArray.hpp"
#include "Main_f.hpp"

// g++ -I include -L lib -o main src/* -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf  -Wall

int main ( int argc, char *argv[] )
{

    SDL_Window* window = initializeVisualSort();
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* arial =  TTF_OpenFont("Arial.ttf", 20);
    if( arial == NULL )
    {
        std::cout << "Couldn't find font." << std::endl;
    }
    
    SDL_Rect i_rect;
    i_rect.x = 000;
    i_rect.y = 100;
    i_rect.w = 175;
    i_rect.h = 300;

    SDL_Color white = {255, 255, 255};
    int array[2] = {10, 6};
    int size = 2;
    VisualArray main(array, size, i_rect, arial, white, renderer);

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

        SDL_RenderClear(renderer);
        main.renderArray();
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    std::cout << "Success!" << std::endl;
    destroyVisualSort(window, arial);
    return 0;
}