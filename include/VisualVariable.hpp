#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "VisualNumber.hpp"

class VisualVariable
{
public:
    VisualVariable();
    VisualVariable(std::string name, const int value_,  TTF_Font* font_ptr, SDL_Renderer* renderer_ptr);
    void setValue(const int value_, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr) 
        {  value.setValue(value_, font_ptr, renderer_ptr);  };
    VisualNumber* getNumber() {  return &value;  }
    std::string getName() {  return name;  };
    void renderCopy(SDL_Renderer* renderer_ptr, 
                            const unsigned short window_height, const unsigned short window_width, 
                            TTF_Font* font_ptr, unsigned short* time_counter_ptr,
                            SDL_Texture* red_square_texture_ptr);
    void renderCopyArray(VisualVariable visualVarables[], short number_of_variables,
                                     SDL_Renderer* renderer_ptr, 
                                     const unsigned short window_height, 
                                     const unsigned short window_width, 
                                     TTF_Font* font_ptr, unsigned short* time_counter_ptr,
                                     SDL_Texture* red_square_texture_ptr);
    void setComparing(bool boolean) {  value.setComparing(boolean);  };
private:
    std::string name;
    VisualNumber value;
};