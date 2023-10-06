#include <stdio.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

// g++ -I include -L lib -o main src/* -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf  -Wall

int main ( int argc, char *argv[] )
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "Hey.. SDL_Init HAS FAILED: SDL_ERROR " << SDL_GetError() << std::endl;
    }

    if(!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
    }

    if(TTF_Init() != 0)
    {
        std::cout << "TTF_init has failed. Error: " << TTF_GetError() << std::endl;
    }

    
    SDL_Window* window = SDL_CreateWindow(
        "VisualSort V0", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        1280, 1000, 
        SDL_WINDOW_SHOWN
        );

    if(window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* Arial =  TTF_OpenFont("Arial.ttf", 24);
    if(Arial == NULL)
    {
        std::cout << "Couldn't find fount." << std::endl;
    }
    SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Arial, "Testee", White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = 000;
    Message_rect.y = 100;
    Message_rect.w = 300;
    Message_rect.h = 300;

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
        SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
        SDL_RenderPresent(renderer);
    }

    std::cout << "Success!" << std::endl;

    SDL_DestroyWindow(window);
    SDL_DestroyTexture(Message);
    TTF_CloseFont(Arial);
    TTF_Quit();
    SDL_Quit();

    return 0;
}