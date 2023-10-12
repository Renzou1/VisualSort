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
#include "Main_f.hpp"

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
    int array[SIZE] = {4, 6, 2, 9, 3, 1, 5};
    
    Configuration config = {renderer_ptr, NULL, &event, font_ptr, window_ptr};
    //selectionSort(array, config);

    bool upPointer = false;
    VisualArray visualArray = makeVisualArray(array, 2, &config);
    visualArray.addPointer(upPointer, 0, font_ptr, "smallest");
    visualArray.addPointer(!upPointer, 0, font_ptr, "j");
    

    bool running = true;
    
    bool flag = true;
    
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
            if (!visualArray.incrementPointer("smallest", config))
            {  break;  }
            flag = false;  
            if (!visualArray.swap(0, 4, config))
            {  break;  }
        }
        SDL_RenderPresent(renderer_ptr);
        //SDL_Delay(10 / SPEED); delays should probably be more local
    }

    return 0;
}