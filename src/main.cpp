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
    //selectionSort(array, config);

    bool upPointer = true;
    VisualArray visualArray = makeVisualArray(array, 3, &config);
    int j = 0;
    visualArray.addPointer(upPointer, 0, font_ptr, "i");
    int i = 0;
    visualArray.addPointer(upPointer, 0, font_ptr, "j");
    int min = 0;
    visualArray.addPointer(!upPointer, 0, font_ptr, "min");
    
    
    while(i < SIZE)
    {
        waitForInput(&config);
        j = i;
        visualArray.slidePointer("j", "i", &config);
        while(j < SIZE)
        {
            if(array[j] < array[min])
            {
                waitForInput(&config);
                visualArray.slidePointer("min", "j", &config);
                min = j;
            }
            waitForInput(&config);
            j++;
            visualArray.incrementPointer("j", &config);
        }
        waitForInput(&config);
        visualArray.swapElementsPointedBy("i", "min", &config);
        swap(&array[i], &array[min]);
        waitForInput(&config);
        i++;
        visualArray.incrementPointer("i", &config);
    }

    waitForInput(&config);
    destroyVisualSort(&config);
    return 0;
}