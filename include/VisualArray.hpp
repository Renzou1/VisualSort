#include <VisualNumber.hpp>
#include <iostream>

class VisualArray
{
public:
    VisualArray(int array[], int size, 
                SDL_Rect* first_rect_ptr, SDL_Texture* red_square_texture_ptr, 
                TTF_Font* font_ptr, SDL_Color color, SDL_Renderer* renderer_ptr);
    void split();
    void swap();
    void renderArray();
    int getVal(int index);
private:
    int size;
    SDL_Texture* red_square_texture_ptr;
    SDL_Rect* first_rect_ptr;
    SDL_Renderer* renderer_ptr;
    VisualNumber* visualArray;
};