#include <VisualArray.hpp>

VisualArray::VisualArray(int array[], int size, 
                        SDL_Rect first_rect, TTF_Font* font, SDL_Color color, SDL_Renderer* renderer)
{
    this->size = size;
    this->first_rect = &first_rect;
    this->renderer = renderer;
    visualArray = new VisualNumber[size];
    for(int i = 0; i < size; i++)
    {
        this->visualArray[i] = VisualNumber(array[i], font, color, renderer);
    }
}

void VisualArray::renderArray()
{
    SDL_Rect temp_rect = *first_rect;
    for(int i = 0; i < size; i++)
    {
        temp_rect.x += 200*i;
        SDL_RenderCopy(renderer, visualArray[i].getTexture(), NULL, &temp_rect);
    }
}