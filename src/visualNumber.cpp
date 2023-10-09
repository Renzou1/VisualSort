#include <VisualNumber.hpp>
#include <iostream>

VisualNumber::VisualNumber()
:val(0), number_texture(NULL)
{}

VisualNumber::VisualNumber(int val, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr)
{
    this->val = val;
    //create number texture:
    SDL_Color white = {255, 255, 255};
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font_ptr, std::to_string(val).c_str(), white);
    number_texture = SDL_CreateTextureFromSurface(renderer_ptr, temp_surface);
    SDL_FreeSurface(temp_surface);
}

SDL_Texture* VisualNumber::getTexture()
{  return number_texture;  }

int VisualNumber::getVal()
{  return val;  }

void VisualNumber::destroy()
{  SDL_DestroyTexture(number_texture);  }

