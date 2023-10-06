#include <stdio.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

// g++ -I include -L lib -o main src/* -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -Wall

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

    RenderWindow window("GAME V1.0", 1280, 720);
    SDL_Texture* grassTexture = window.loadTexture("resources/gfx/grass.png");


    Entity platform0(100, 300, grassTexture);

    bool gameRunning = true;
    SDL_Event event;
    
    while (gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
        }

        window.clear();
        platform0.xpp();
        window.render(platform0);
        window.display();
    }

    std::cout << "Success!" << std::endl;

    window.cleanUp();
    SDL_Quit();

    return 0;
}