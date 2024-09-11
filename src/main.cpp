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

// g++ -I include -o main src/* -lSDL2 -lSDL2_image -lSDL2_ttf -pthread -Wall
// TODO: make makefile
// TODO: insertion sort, quick sort, merge sort
// TODO: change flag 2 name in visualNumber
// TODO: render swap, increments and comparison count
// TODO: should swap count when with itself in selection sort? currently we skip swap if index == index

int main ( int argc, char *argv[] )
{
    srand(time(NULL));
    std::cout << "How many elements in your array? (60 max)" << std::endl;

    int size;
    scanf("%d", &size);
    if (size < 2 ) { size =  2; }
    if (size > 60) { size = 60; }
    int* array = (int*)malloc(sizeof(int)* size); 

    printf("1- Random numbers\n2- Choose numbers\n");
    int choice;
    scanf("%d", &choice);
    if(choice == 1)
    {
        for(int i = 0; i < size; i++)
        {
            array[i] = rand() % 100;
        }
    }  else
    {
        std::cout << "Type your desired array: (example: 20 5 7 4 3)" << std::endl;

        for(int i = 0; i < size; i++)
        {
            int temp;
            scanf("%d", &temp);
            std::cout << "here" << std::endl;
            if (temp <  0){  temp*=-1;  }
            if (temp > 99){  temp%=100; }
            array[i] = temp;
        }
    }
    
    SDL_DisplayMode dm;
    int width;
    const int default_width = 1920;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
    {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s; will assume screen width of 1920", SDL_GetError());
        width = default_width;
    }  else {
        width = dm.w;
    }

    int font_size = INITIAL_FONT_SIZE;
    if(font_size * 2 * size + font_size * 2 > width)
    {
        // scales font size depending on screen width and array size
        font_size = (width - 200)/ (2 * size);
    }

    std::cout << "Please select the sorting algorithm.\n";
    std::cout << "1. selectionsort\n2. insertionsort\n3. quicksort\n4. mergesort\n";
    unsigned int algorithm;
    scanf("%d", &algorithm);
    while(algorithm < 0 || algorithm > 4)
    {
        std::cout << "invalid number, try again.\n";
        scanf("%d", &algorithm);
    }    

    TTF_Font* font_ptr = initializeFont(font_size);
    const int double_digit_width = getDoubleDigitWidth(font_ptr);
    SDL_Window* window_ptr = initializeVisualSort(size, double_digit_width, algorithm);
    SDL_Renderer* renderer_ptr = SDL_CreateRenderer(window_ptr, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_Event event;    
    Configuration config = {renderer_ptr, NULL, &event, font_ptr, window_ptr, size, double_digit_width};

    switch (algorithm){
        case SELECTION_SORT:
            selectionSort(array, &config);
            break;
        case INSERTION_SORT:
            break;
        case MERGE_SORT:
            break;
        case QUICK_SORT:
            break;
        
    }

    return 0;
}