#include "VisualVariable.hpp"

VisualVariable::VisualVariable()
:name(""), value(VisualNumber())
{}

VisualVariable::VisualVariable(std::string name, const int value_, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr)
{
    this->name = name;
    this->value = VisualNumber(value_, font_ptr, renderer_ptr);
}


void VisualVariable::renderCopy(SDL_Renderer* renderer_ptr, 
                            const unsigned short window_height, const unsigned short window_width, 
                            TTF_Font* font_ptr, unsigned short* time_counter_ptr,
                            SDL_Texture* red_square_texture_ptr)
{
    std::string variable_string = name + " = ";// + std::to_string(value.getValue());
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
    info_rect.y = 20;

    SDL_Rect number_rect;
    // only needs these two
    number_rect.x = info_rect.x + info_rect.w;
    value.setX(number_rect.x);
    number_rect.y = info_rect.y;
    value.setY(number_rect.y);

    value.renderCopy(time_counter_ptr, &number_rect, red_square_texture_ptr, renderer_ptr);    

    SDL_RenderCopy(renderer_ptr, variable_texture, NULL, &info_rect);
    SDL_FreeSurface(variable_surface);
    SDL_DestroyTexture(variable_texture);
}

void VisualVariable::renderCopyArray(VisualVariable visualVariables[], short number_of_variables,
                                     SDL_Renderer* renderer_ptr, 
                                     const unsigned short window_height, 
                                     const unsigned short window_width, 
                                     TTF_Font* font_ptr, unsigned short* time_counter_ptr,
                                     SDL_Texture* red_square_texture_ptr)
{
    SDL_Color WHITE = {255, 255, 255};
    std::string strings[number_of_variables];
    SDL_Surface* surfaces[number_of_variables];
    SDL_Texture* textures[number_of_variables];
    for(int i = 0; i < number_of_variables; i++)
    {
        strings[i] = visualVariables[i].name + " = ";
        surfaces[i] = TTF_RenderText_Solid(font_ptr, strings[i].c_str(), WHITE);
        if (surfaces[i] == NULL){
            std::cout << "Error:" << TTF_GetError() << std::endl;
        }
        textures[i] = SDL_CreateTextureFromSurface(renderer_ptr, surfaces[i]);
    }

    SDL_Rect rects[number_of_variables];
    short total_width = 0;
    for(int i = 0; i < number_of_variables; i++)
    {
        rects[i].w = surfaces[i]->w;
        rects[i].h = surfaces[i]->h;
        rects[i].y = 20;
        if(surfaces[i]->h < (int) TEXT_HEIGHT) // if font is smol
        {
            rects[i].y += TEXT_HEIGHT/4;
        }
        total_width += rects[i].w;
        if(i + 1 < number_of_variables)
        {
            total_width += DISTANCE_BETWEEN_VARIABLE_STRINGS;
        }
        if(visualVariables[i].getValue()->getValue() < 10)
        {
            total_width += SINGLE_DIGIT_WIDTH;
        }  else {
            total_width += DOUBLE_DIGIT_WIDTH;
        }
    }

    for(int i = 0, cumulative_width = 0; i < number_of_variables; i++)
    {
        rects[i].x = window_width/2 - total_width/2 + cumulative_width;
        cumulative_width += rects[i].w;
        if(i + 1 < number_of_variables)
        {
            cumulative_width += DISTANCE_BETWEEN_VARIABLE_STRINGS;
        }
        if(visualVariables[i].getValue()->getValue() < 10)
        {
            cumulative_width += SINGLE_DIGIT_WIDTH;
        }  else {
            cumulative_width += DOUBLE_DIGIT_WIDTH;
        }
    }

    SDL_Rect number_rects[number_of_variables];
    for(int i = 0; i < number_of_variables; i++)
    {
        number_rects[i].y = 20;
        number_rects[i].x = rects[i].x + rects[i].w;
        visualVariables[i].getValue()->setX(number_rects[i].x);
        visualVariables[i].getValue()->setY(number_rects[i].y);
    }

    for(int i = 0; i < number_of_variables; i++)
    {
        visualVariables[i].getValue()->renderCopy(time_counter_ptr, &number_rects[i], 
                                                red_square_texture_ptr, renderer_ptr);
        SDL_RenderCopy(renderer_ptr, textures[i], NULL, &rects[i]);
        SDL_FreeSurface(surfaces[i]); 
        SDL_DestroyTexture(textures[i]);                                     
    }
}