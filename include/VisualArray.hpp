#pragma once

#include <VisualNumber.hpp>

class VisualArray
{
public:
    VisualArray(int array[], int size, 
                        SDL_Rect first_rect, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
    void split();
    void swap();
    void renderArray();
private:
    int size;
    SDL_Texture* red_square_texture;
    SDL_Rect* first_rect;
    SDL_Renderer* renderer;
    VisualNumber* visualArray;
};