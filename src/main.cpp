#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Main_f.hpp"
#include "Globals.hpp"
#include "VisualArray.hpp"
#include "VisualPointer.hpp"
#include "VisualNumber.hpp"
#include "SortingAlgorithms.hpp"

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

    SDL_Event event;
    int array[SIZE];
    for(int i = 0; i < SIZE; i++)
    {
        array[i] = i;
    }
    
    Configuration config = {renderer_ptr, NULL, &event, font_ptr, window_ptr};
    selectionSort(array, &config);

    waitForInput(&config);
    destroyVisualSort(&config);
    return 0;
}