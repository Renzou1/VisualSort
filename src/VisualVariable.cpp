#include "VisualVariable.hpp"

VisualVariable::VisualVariable()
:name(""), value(VisualNumber())
{}

VisualVariable::VisualVariable(std::string name, const int value_, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr)
{
    this->name = name;
    this->value = VisualNumber(value_, font_ptr, renderer_ptr);
}


void VisualVariable::render(SDL_Renderer* renderer_ptr, 
                            const unsigned int window_height, const unsigned int window_width, 
                            TTF_Font* font_ptr)
{
    std::string variable_string = name + " = " + std::to_string(value.getValue());
    SDL_Color WHITE = {255, 255, 255};
    SDL_Surface* variable_surface = TTF_RenderText_Solid(font_ptr, variable_string.c_str(), WHITE);
    if (variable_surface == NULL){
        std::cout << "Error:" << TTF_GetError() << std::endl;
    }
    SDL_Texture* variable_texture = SDL_CreateTextureFromSurface(renderer_ptr, variable_surface);
    
    SDL_Rect info_rect;
    info_rect.w = variable_surface->w;
    info_rect.h = variable_surface->h;
    info_rect.x = window_width/2 - info_rect.w/2;
    info_rect.y = 0;    

    SDL_RenderCopy(renderer_ptr, variable_texture, NULL, &info_rect);
    SDL_FreeSurface(variable_surface);
}