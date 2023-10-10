#include <VisualArray.hpp>
#include <Globals.hpp>

VisualArray::VisualArray(int array[], int size, int pointersSize, 
                        SDL_Rect* first_rect_ptr, 
                        SDL_Renderer* renderer_ptr,
                        TTF_Font* font_ptr)
{
    currentPointerIndex = 0;
    this->size = size;
    this->first_rect_ptr = first_rect_ptr;
    this->red_square_texture_ptr = IMG_LoadTexture(renderer_ptr, "resources/red_square_texture.png");
    this->renderer_ptr = renderer_ptr;

    visualArray = new VisualNumber[size];
    for(int i = 0; i < size; i++)
    {
        this->visualArray[i] = VisualNumber(array[i], font_ptr, renderer_ptr);
    }
    visualPointers = new VisualPointer[pointersSize];
}

void alignSquareWithNumber(SDL_Rect* number_rect_ptr, SDL_Rect* square_rect_ptr, SDL_Rect* first_rect_ptr)
{
    int spaceBetweenNumbers = DISTANCE - first_rect_ptr->w;
    square_rect_ptr->x = number_rect_ptr->x - spaceBetweenNumbers/2; //needs this to align
    int number_center = number_rect_ptr->y + number_rect_ptr->h/2;
    square_rect_ptr->w = number_rect_ptr->w + spaceBetweenNumbers;
    square_rect_ptr->y = number_center - square_rect_ptr->w/2;
    square_rect_ptr->h = square_rect_ptr->w;
}

void VisualArray::renderArray()
{
    SDL_Rect number_rect;
    number_rect.x = first_rect_ptr->x;
    number_rect.y = first_rect_ptr->y;
    number_rect.h = first_rect_ptr->h;
    number_rect.w = first_rect_ptr->w;

    SDL_Rect red_square_rect;
    for(int i = 0; i < size; i++)
    {
        number_rect.x = first_rect_ptr->x + DISTANCE*i;
        SDL_RenderCopy(renderer_ptr, visualArray[i].getTexture(), NULL, &number_rect);
        alignSquareWithNumber(&number_rect, &red_square_rect, first_rect_ptr);
        SDL_RenderCopy(renderer_ptr, red_square_texture_ptr, NULL, &red_square_rect);
    }

    renderPointers();
}

void VisualArray::renderPointers()
{
    for(int i = 0; i < currentPointerIndex; i++)
    {
        visualPointers[i].render(renderer_ptr);
    }
}

int VisualArray::getVal(int index)
{
    return visualArray[index].getVal();
}

VisualPointer* VisualArray::getPointer(std::string name)
{  
    for(int i = 0; i < currentPointerIndex; i++)
    {
        if(visualPointers[i].getName() == name)
        {
            return &visualPointers[i];
        }
    }

    return NULL;
}
VisualPointer* VisualArray::getPointer(int index)
{   
    for(int i = 0; i < currentPointerIndex; i++)
    {
        if(visualPointers[i].getIndex() == index)
        {
            return &visualPointers[i];
        }
    }

    return NULL;
}

void VisualArray::addPointer(bool isAbovePointer, int index, TTF_Font* font_ptr, std::string name)
{
    SDL_Rect temp_name_rect;
    temp_name_rect.x = first_rect_ptr->x + DISTANCE * index + INDEX_TEXTURE_OFFSET;

    SDL_Rect temp_arrow_rect;
    temp_arrow_rect.w = 100;
    temp_arrow_rect.h = 100;
    temp_arrow_rect.x = first_rect_ptr->x + DISTANCE * index + ARROW_TEXTURE_OFFSET;

    if(isAbovePointer)
    {
        temp_name_rect.y = first_rect_ptr->y - DISTANCE - temp_arrow_rect.h;
        temp_arrow_rect.y = first_rect_ptr->y - 150;

    }  else
    {
        temp_name_rect.y = first_rect_ptr->y + DISTANCE + temp_arrow_rect.h;
        temp_arrow_rect.y = first_rect_ptr->y + 150;
    }
    
    visualPointers[currentPointerIndex] = VisualPointer(isAbovePointer, temp_name_rect, temp_arrow_rect, 
                                                        font_ptr, renderer_ptr, name);
    currentPointerIndex++;
}

void VisualArray::swap(int index1, int index2)
{

}

void VisualArray::destroy()
{
    // dont know if done
    delete [] visualArray;
    delete [] visualPointers;
    SDL_DestroyTexture(red_square_texture_ptr);
}