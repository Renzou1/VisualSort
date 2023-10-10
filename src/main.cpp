#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>

#include "Globals.hpp"
#include "Main_f.hpp"
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
    
    int array[SIZE] = {4, 6, 2, 9, 3, 1, 5};
    SDL_Rect initial_rect = makeInitialRect(array, font_ptr);
    VisualArray visualArray(array, SIZE, 2, &initial_rect, renderer_ptr, font_ptr);
    bool upPointer = false;
    visualArray.addPointer(upPointer, 0, font_ptr, "i");
    visualArray.addPointer(!upPointer, 0, font_ptr, "j");
    //selectionSort(array, SIZE);

    bool running = true;
    SDL_Event event;
    bool flag = true;
    bool flag2 = true;
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
        if(flag)
        {  
            if (!visualArray.getPointer("i")->slidePointer(4, renderer_ptr, &visualArray, &event))
            {  break;  }
            flag = false;  
        }
        if(flag2)
        {  
            if (!visualArray.getPointer("i")->slidePointer(0, renderer_ptr, &visualArray, &event))
            {  break;  }
            flag2 = false;  
        }
        SDL_RenderPresent(renderer_ptr);
        //SDL_Delay(10 / SPEED); delays should probably be more local
    }

    destroyVisualSort(window_ptr, font_ptr, &visualArray);
    return 0;
}