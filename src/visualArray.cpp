#include <VisualArray.hpp>
#include <VisualNumber.hpp>
#include <Globals.hpp>

VisualArray::VisualArray(int array[], int size, 
                        SDL_Rect* first_rect_ptr, SDL_Texture* red_square_texture_ptr, 
                        TTF_Font* font_ptr, SDL_Color color, SDL_Renderer* renderer_ptr)
{
    this->size = size;
    this->first_rect_ptr = first_rect_ptr;
    this->red_square_texture_ptr = red_square_texture_ptr;
    this->renderer_ptr = renderer_ptr;
    visualArray = new VisualNumber[size];
    for(int i = 0; i < size; i++)
    {
        this->visualArray[i] = VisualNumber(array[i], font_ptr, color, renderer_ptr);
    }
}

void VisualArray::renderArray()
{
    SDL_Rect number_rect;
    number_rect.h = first_rect_ptr->h;
    number_rect.w = first_rect_ptr->w;
    number_rect.x = first_rect_ptr->x;
    number_rect.y = first_rect_ptr->y;

    SDL_Rect red_square_rect;
    for(int i = 0; i < size; i++)
    {
        number_rect.x = first_rect_ptr->x + DISTANCE*i;
        SDL_RenderCopy(renderer_ptr, visualArray[i].getTexture(), NULL, &number_rect);

        int spaceBetweenNumbers = DISTANCE - first_rect_ptr->w;
        red_square_rect.x = number_rect.x - spaceBetweenNumbers/2; //needs this to align
        int number_center = number_rect.y + number_rect.h/2;
        red_square_rect.w = number_rect.w + spaceBetweenNumbers;
        red_square_rect.y = number_center - red_square_rect.w/2;
        red_square_rect.h = red_square_rect.w;
        SDL_RenderCopy(renderer_ptr, red_square_texture_ptr, NULL, &red_square_rect);
    }
}

int VisualArray::getVal(int index)
{
    return visualArray[index].getVal();
}