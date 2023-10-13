#include "VisualArray.hpp"
#include "Globals.hpp"

void destroyVisualSort(Configuration* config);

VisualArray::VisualArray(int array[], int size, int pointersSize, 
                        SDL_Rect first_rect, 
                        SDL_Renderer* renderer_ptr,
                        TTF_Font* font_ptr)
{
    currentPointerIndex = 0;
    this->size =                   size;
    this->first_rect             = first_rect;
    this->red_square_texture_ptr = IMG_LoadTexture(renderer_ptr, "resources/red_square_texture.png");
    this->renderer_ptr =           renderer_ptr;
    this->pointersSize =           pointersSize;

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
    square_rect_ptr->x      = number_rect_ptr->x - spaceBetweenNumbers/2; //needs this to align
    int number_center       = number_rect_ptr->y + number_rect_ptr->h/2;
    square_rect_ptr->w      = number_rect_ptr->w + spaceBetweenNumbers;
    square_rect_ptr->y      = number_center - square_rect_ptr->w/2;
    square_rect_ptr->h      = square_rect_ptr->w;
}

void VisualArray::renderArray()
{
    SDL_Rect number_rect;
    number_rect.x = first_rect.x;
    number_rect.y = first_rect.y;
    number_rect.h = first_rect.h;
    number_rect.w = first_rect.w;

    SDL_Rect red_square_rect;
    for(int i = 0; i < size; i++)
    {
        number_rect.x = first_rect.x + DISTANCE*i;
        if(visualArray[i].shouldntSkip())
        {  SDL_RenderCopy(renderer_ptr, visualArray[i].getTexture(), NULL, &number_rect);  }
        alignSquareWithNumber(&number_rect, &red_square_rect, &first_rect);
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

    std::cout << "failed to find pointer named " << name << std::endl;
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

void VisualArray::slidePointer(std::string name, int _index, Configuration* config_ptr)
{
    VisualPointer* pointer = getPointer(name);
    if(pointer == NULL)
    {  
        std::cout << "couldnt find pointer" << std::endl;
        destroyVisualSort(config_ptr);  
    }
    SDL_Renderer* renderer_ptr = config_ptr->renderer_ptr;
    SDL_Event* event_ptr = config_ptr->event_ptr;
    VisualArray* visualArray_ptr = config_ptr->visualArray_ptr;

    int initial_x = pointer->getNameRect()->x;
    int distanceToIndex = _index - pointer->getIndex();
    int increment = _index - pointer->getIndex();
    int goal_x = initial_x + distanceToIndex * DISTANCE;

    while(pointer->getNameRect()->x != goal_x)
    {
        while (SDL_PollEvent(event_ptr))
        {
            if (event_ptr->type == SDL_QUIT)
            {
                destroyVisualSort(config_ptr);
            }
        }
        pointer->getNameRect()->x+= increment; // speed is based on distance 
        pointer->getArrowRect()->x+= increment;
        SDL_RenderClear(renderer_ptr);
        SDL_RenderCopy(renderer_ptr, pointer->getNameTexturePtr(), NULL, pointer->getNameRect());
        SDL_RenderCopy(renderer_ptr, pointer->getArrowTexturePtr(), NULL, pointer->getArrowRect());
        visualArray_ptr->renderArray();
        SDL_RenderPresent(renderer_ptr);
        SDL_Delay(10 / SPEED);
    }
    pointer->setIndex(_index);
}

void VisualArray::slidePointer(std::string name, std::string name2, Configuration* config_ptr)
{
    VisualPointer* pointer = getPointer(name);
    int _index = getPointer(name2)->getIndex();
    if(pointer == NULL)
    {  
        std::cout << "couldnt find pointer" << std::endl;
        destroyVisualSort(config_ptr);  
    }
    if(pointer->getIndex() == _index)
    {  return;  }
    SDL_Renderer* renderer_ptr = config_ptr->renderer_ptr;
    SDL_Event* event_ptr = config_ptr->event_ptr;
    VisualArray* visualArray_ptr = config_ptr->visualArray_ptr;

    int initial_x = pointer->getNameRect()->x;
    int distanceToIndex = _index - pointer->getIndex();
    int increment = _index - pointer->getIndex();
    int goal_x = initial_x + distanceToIndex * DISTANCE;

    while(pointer->getNameRect()->x != goal_x)
    {
        while (SDL_PollEvent(event_ptr))
        {
            if (event_ptr->type == SDL_QUIT)
            {
                destroyVisualSort(config_ptr);
            }
        }
        pointer->getNameRect()->x+= increment; // speed is based on distance 
        pointer->getArrowRect()->x+= increment;
        SDL_RenderClear(renderer_ptr);
        SDL_RenderCopy(renderer_ptr, pointer->getNameTexturePtr(), NULL, pointer->getNameRect());
        SDL_RenderCopy(renderer_ptr, pointer->getArrowTexturePtr(), NULL, pointer->getArrowRect());
        visualArray_ptr->renderArray();
        SDL_RenderPresent(renderer_ptr);
        SDL_Delay(10 / SPEED);
    }
    pointer->setIndex(_index);

}

void VisualArray::incrementPointer(std::string name, Configuration* config_ptr)
{
    slidePointer(name, getPointer(name)->getIndex() + 1, config_ptr);
}

void VisualArray::decrementPointer(std::string name, Configuration* config_ptr)
{
    slidePointer(name, getPointer(name)->getIndex() - 1, config_ptr);
}

void VisualArray::addPointer(bool isAbovePointer, int index, TTF_Font* font_ptr, std::string name)
{
    SDL_Color white = {255, 255, 255};
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font_ptr, name.c_str(), white);
    SDL_Texture* name_texture_ptr = SDL_CreateTextureFromSurface(renderer_ptr, temp_surface);

    SDL_Rect temp_name_rect;
    temp_name_rect.x = first_rect.x + DISTANCE * index + first_rect.w/2 - temp_surface->w/2; //+ INDEX_TEXTURE_OFFSET - middle;

    SDL_Rect temp_arrow_rect;
    temp_arrow_rect.w = FONT_SIZE * 1.25;
    temp_arrow_rect.h = FONT_SIZE * 1.25;
    temp_arrow_rect.x = first_rect.x - temp_arrow_rect.w/2 + first_rect.w/2;

    if(isAbovePointer)
    {
        temp_name_rect.y =  first_rect.y - DISTANCE - temp_arrow_rect.h;
        temp_arrow_rect.y = first_rect.y - temp_arrow_rect.h * ARROW_DISTANCE_MULTIPLIER; // guess

    }  else
    {
        temp_name_rect.y =  first_rect.y + DISTANCE + temp_arrow_rect.h;
        temp_arrow_rect.y = first_rect.y + temp_arrow_rect.h * ARROW_DISTANCE_MULTIPLIER;
    }
    temp_name_rect.w = temp_surface->w;
    temp_name_rect.h = temp_surface->h;
    
    visualPointers[currentPointerIndex] = VisualPointer(isAbovePointer, temp_name_rect, temp_arrow_rect, 
                                                        font_ptr, renderer_ptr, name, name_texture_ptr);
    currentPointerIndex++;
    SDL_FreeSurface(temp_surface);
}

void VisualArray::swapElementsInArray(int index1, int index2)
{
    VisualNumber temp;
    temp = visualArray[index1];
    visualArray[index1] = visualArray[index2];
    visualArray[index2] = temp;
}

void VisualArray::swap(int index1, int index2, Configuration* config_ptr)
{
    SDL_Renderer* renderer_ptr = config_ptr->renderer_ptr;
    SDL_Event* event_ptr = config_ptr->event_ptr;
    VisualArray* visualArray_ptr = config_ptr->visualArray_ptr;
    visualArray[index1].skipRender();
    visualArray[index2].skipRender();

    int index1_initial_x = first_rect.x + index1*DISTANCE;
    int index1_current_x = index1_initial_x;
    int index2_x         = first_rect.x + index2*DISTANCE;
    int index2_current_x = index2_x;
    int increment        = index1 - index2;
    SDL_Rect temp_rect;
    temp_rect.w = first_rect.w;
    temp_rect.h = first_rect.h; 
    temp_rect.y = first_rect.y;
    temp_rect.x = index1_current_x;

    while(index1_current_x != index2_x)
    {
        while (SDL_PollEvent(event_ptr))
        {
            if (event_ptr->type == SDL_QUIT)
            {
                destroyVisualSort(config_ptr);
            }
        }

        index1_current_x-= increment;
        index2_current_x+= increment;

        SDL_RenderClear(renderer_ptr);
        temp_rect.x = index1_current_x;
        SDL_RenderCopy(renderer_ptr, visualArray[index1].getTexture(), NULL, &temp_rect);
        temp_rect.x = index2_current_x;
        SDL_RenderCopy(renderer_ptr, visualArray[index2].getTexture(), NULL, &temp_rect);
        visualArray_ptr->renderArray();
        SDL_RenderPresent(renderer_ptr);
        SDL_Delay(10 / SPEED);
    } 
    visualArray[index1].unskip();
    visualArray[index2].unskip(); 
    swapElementsInArray(index1, index2);
}

void VisualArray::operator=(const VisualArray& V)
{
    size = V.size;
    currentPointerIndex = V.currentPointerIndex;
    red_square_texture_ptr = V.red_square_texture_ptr;
    first_rect =  V.first_rect;
    renderer_ptr = V.renderer_ptr;
    for(int i = 0; i < size; i++)
    {
        visualArray[i] = V.visualArray[i];
    }
    for(int i = 0; i < pointersSize; i++)
    {
        visualPointers[i] = V.visualPointers[i];
    }
}

void VisualArray::swapElementsPointedBy(std::string pointer1, std::string pointer2, Configuration* config_ptr)
{
    swap(getPointer(pointer1)->getIndex(), getPointer(pointer2)->getIndex(), config_ptr);
}
void VisualArray::destroy()
{
    // dont know if done
    delete [] visualArray;
    delete [] visualPointers;
    SDL_DestroyTexture(red_square_texture_ptr);
}