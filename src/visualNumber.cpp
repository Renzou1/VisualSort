#include <VisualNumber.hpp>
#include <iostream>

VisualNumber::VisualNumber()
:val(0), number_texture(NULL)
{}

VisualNumber::VisualNumber(int val, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
{
    this->val = val;
    //create number texture:
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font, std::to_string(val).c_str(), color);
    number_texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
}

SDL_Texture* VisualNumber::getTexture()
{  return number_texture;  }

int VisualNumber::getVal()
{  return val;  }

