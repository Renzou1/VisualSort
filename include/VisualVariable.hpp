#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

class VisualVariable
{
public:
    VisualVariable();
    VisualVariable(std::string name, const int value);
    void render(SDL_Renderer* renderer_ptr, const unsigned int window_height, 
                const unsigned int window_width, TTF_Font* font_ptr);
private:
    std::string name;
    int value;
};