#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Main_f.hpp"
#include "Globals.hpp"
#include "VisualArray.hpp"
#include "VisualPointer.hpp"
#include "VisualNumber.hpp"
#include "SortingAlgorithms.hpp"

// g++ -I include -L lib -o main src/* -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf  -Wall
// g++ -I include -o main src/* -lSDL2 -lSDL2_image -lSDL2_ttf -pthread -Wall
// TODO: red_square_texture png size is probably off, boxes dont align perfectly.

int main ( int argc, char *argv[] )
{
    srand(time(NULL));
    std::cout << "How many elements in your array? (60 max)" << std::endl;

    int size;
    scanf("%d", &size);
    if (size > 60) { size = 60; }
    int* array = (int*)malloc(sizeof(int)* size); 

    printf("1- Random numbers\n2- Choose numbers\n");
    int choice;
    int i = 0;    
    scanf("%d", &choice);
    if(choice == 1)
    {
        for(i = 0; i < size; i++)
        {
            array[i] = rand() % 100;
        }
    }  else
    {
        std::cout << "Type your desired array:" << std::endl;

        for(i = 0; i < size; i++)
        {
            scanf("%d", &array[i]);
        }
    }
    while(i < size)
    {  SDL_Delay(10);  }

    int font_size = 80;
    if(DISTANCE * size + DISTANCE > 1920)
    {
        font_size = 1720/ (2 * size);
    }
    std::cout << font_size;
        
    SDL_Window* window_ptr = initializeVisualSort(size, font_size);
    SDL_Renderer* renderer_ptr = SDL_CreateRenderer(window_ptr, -1, SDL_RENDERER_PRESENTVSYNC);
    TTF_Font* font_ptr =  TTF_OpenFont("Rubik-Regular.ttf", font_size);
    if( font_ptr == NULL )
    {
        std::cout << "Couldn't find font." << std::endl;
    }
    SDL_Event event;    
    Configuration config = {renderer_ptr, NULL, &event, font_ptr, window_ptr, size, font_size};
    selectionSort(array, &config);

    return 0;
}