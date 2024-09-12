#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <VisualNumber.hpp>

class VisualVariable
{
public:
    VisualVariable();
    VisualVariable(std::string name, const int value_,  TTF_Font* font_ptr, SDL_Renderer* renderer_ptr);
    void setValue(const int value_, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr) 
        {  value.setValue(value_, font_ptr, renderer_ptr);  };
    std::string getName() {  return name;  };
    void render(SDL_Renderer* renderer_ptr, const unsigned int window_height, 
                const unsigned int window_width, TTF_Font* font_ptr);
    void setComparing(bool boolean) {  value.setComparing(boolean);  };
private:
    std::string name;
    VisualNumber value;
};