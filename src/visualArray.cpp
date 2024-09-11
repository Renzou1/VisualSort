#include "VisualArray.hpp"
#include "Globals.hpp"

void destroyVisualSort(Configuration* config);

VisualArray::VisualArray(const int array[], const unsigned int size, const unsigned int pointersSize, 
                        SDL_Rect initial_digit_rect, 
                        SDL_Renderer* renderer_ptr,
                        TTF_Font* font_ptr)
{
    currentPointerIndex = 0;
    this->size =                   size;
    this->initial_digit_rect       = initial_digit_rect;
    this->red_square_texture_ptr = IMG_LoadTexture(renderer_ptr, "textures/red_square.png");
    this->renderer_ptr =           renderer_ptr;
    this->pointersSize =           pointersSize;

    SDL_Surface* temp_surface = TTF_RenderText_Solid(font_ptr, "0", {255, 255, 255});
    this->single_digit_width = temp_surface->w;
    SDL_FreeSurface(temp_surface);
    this->double_digit_width = initial_digit_rect.w; // width is almost identical to font size, but not quite

    visualArray = new VisualNumber[size];
    for(unsigned int i = 0; i < size; i++)
    {
        this->visualArray[i] = VisualNumber(array[i], font_ptr, renderer_ptr);
    }
    visualPointers = new VisualPointer[pointersSize];
}

void alignSquareWithNumber(SDL_Rect* number_rect_ptr, SDL_Rect* square_rect_ptr, const unsigned int double_digit_width)
{
    square_rect_ptr->w      = RED_SQUARE_WIDTH;
    square_rect_ptr->h      = square_rect_ptr->w;
    square_rect_ptr->x      = number_rect_ptr->x - double_digit_width/2;
    int number_center       = number_rect_ptr->y + number_rect_ptr->h/2;
    square_rect_ptr->y      = number_center - double_digit_width;
}

void VisualArray::renderArray()
{
    SDL_Rect number_rect;
    number_rect.x = initial_digit_rect.x;
    number_rect.y = initial_digit_rect.y;
    number_rect.h = initial_digit_rect.h;
    number_rect.w = initial_digit_rect.w;

    SDL_Rect red_square_rect;
    alignSquareWithNumber(&number_rect, &red_square_rect, double_digit_width);
    for(unsigned int i = 0; i < size; i++)
    {   
        if(visualArray[i].shouldntSkip())
        {
            if(visualArray[i].getVal() >= 10)
            {  
                number_rect.w = double_digit_width;  
                SDL_RenderCopy(renderer_ptr, visualArray[i].getTexture(), NULL, &number_rect);

            }  else
            {  
                number_rect.w = single_digit_width;

                int difference_in_centers = double_digit_width/2 - single_digit_width/2;
                
                number_rect.x += difference_in_centers;
                SDL_RenderCopy(renderer_ptr, visualArray[i].getTexture(), NULL, &number_rect);
                number_rect.x -= difference_in_centers;
            }
             
        }
        SDL_RenderCopy(renderer_ptr, red_square_texture_ptr, NULL, &red_square_rect);
        if(visualArray[i].isComparing())
        {
            int time = 120;
            int flag2 = visualArray[i].getFlag2();
            if(flag2 < time/2)
            {
                SDL_Rect temp_square_rect = red_square_rect;
                temp_square_rect.w = red_square_rect.w*0.8;
                temp_square_rect.h = red_square_rect.h*0.8;

                int length_difference = red_square_rect.w - temp_square_rect.w;
                temp_square_rect.x = red_square_rect.x + (length_difference/2);
                temp_square_rect.y = red_square_rect.y + (length_difference/2);

                SDL_RenderCopy(renderer_ptr, red_square_texture_ptr, NULL, &temp_square_rect);
            }  else if (flag2 > time)
            {  visualArray[i].resetFlag2();  }

            visualArray[i].incrementFlag2();
        }
        number_rect.x += RED_SQUARE_WIDTH;
        red_square_rect.x += RED_SQUARE_WIDTH;
    }

    renderPointers();
}

void VisualArray::renderPointers()
{
    for(index_t i = 0; i < currentPointerIndex; i++)
    {
        visualPointers[i].render(renderer_ptr);
    }
}

int VisualArray::getVal(index_t index)
{
    return visualArray[index].getVal();
}

VisualPointer* VisualArray::getPointer(std::string name)
{  
    for(index_t i = 0; i < currentPointerIndex; i++)
    {
        if(visualPointers[i].getName() == name)
        {
            return &visualPointers[i];
        }
    }

    std::cout << "failed to find pointer named " << name << std::endl;
    return NULL;
}
VisualPointer* VisualArray::getPointer(index_t index)
{   
    for(index_t i = 0; i < currentPointerIndex; i++)
    {
        if(visualPointers[i].getIndex() == index)
        {
            return &visualPointers[i];
        }
    }

    return NULL;
}

void VisualArray::slidePointer(std::string name, index_t _index, Configuration* config_ptr)
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
    int goal_x = initial_x + distanceToIndex * RED_SQUARE_WIDTH;

    while(pointer->getNameRect()->x != goal_x)
    {
        while (SDL_PollEvent(event_ptr))
        {
            if (event_ptr->type == SDL_QUIT)
            {
                destroyVisualSort(config_ptr);
            }
        }
        for(int i = 0; i < SPEED && pointer->getNameRect()->x != goal_x; i++)
        {
            pointer->getNameRect()->x+= increment;
            pointer->getArrowRect()->x+= increment;
        }
        SDL_RenderClear(renderer_ptr);
        SDL_RenderCopy(renderer_ptr, pointer->getNameTexturePtr(), NULL, pointer->getNameRect());
        SDL_RenderCopy(renderer_ptr, pointer->getArrowTexturePtr(), NULL, pointer->getArrowRect());
        visualArray_ptr->renderArray();
        SDL_RenderPresent(renderer_ptr);
    }
    pointer->setIndex(_index);
}

void VisualArray::slidePointer(std::string name, std::string name2, Configuration* config_ptr)
{
    int _index = getPointer(name2)->getIndex();
    slidePointer(name, _index, config_ptr);
}

void VisualArray::incrementPointer(std::string name, Configuration* config_ptr)
{
    slidePointer(name, getPointer(name)->getIndex() + 1, config_ptr);
}

void VisualArray::decrementPointer(std::string name, Configuration* config_ptr)
{
    slidePointer(name, getPointer(name)->getIndex() - 1, config_ptr);
}

void VisualArray::addPointer(bool isAbovePointer, index_t index, TTF_Font* font_ptr, std::string name)
{
    SDL_Color white = {255, 255, 255};
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font_ptr, name.c_str(), white);
    SDL_Texture* name_texture_ptr = SDL_CreateTextureFromSurface(renderer_ptr, temp_surface);

    SDL_Rect temp_name_rect;
    temp_name_rect.x = initial_digit_rect.x + RED_SQUARE_WIDTH * index + double_digit_width/2 - temp_surface->w/2;

    SDL_Rect temp_arrow_rect;
    temp_arrow_rect.w = double_digit_width * 1.25;
    temp_arrow_rect.h = double_digit_width * 1.25;
    temp_arrow_rect.x = initial_digit_rect.x + RED_SQUARE_WIDTH * index - temp_arrow_rect.w/2 + double_digit_width/2;

    if(isAbovePointer)
    {
        temp_arrow_rect.y = initial_digit_rect.y - temp_arrow_rect.h * ARROW_DISTANCE_MULTIPLIER; // guess
        temp_name_rect.y =  temp_arrow_rect.y - temp_arrow_rect.h;

    }  else
    {
        temp_arrow_rect.y = initial_digit_rect.y + temp_arrow_rect.h * ARROW_DISTANCE_MULTIPLIER;
        temp_name_rect.y =  temp_arrow_rect.y + temp_arrow_rect.h;
    }
    temp_name_rect.w = temp_surface->w;
    temp_name_rect.h = temp_surface->h;
    
    visualPointers[currentPointerIndex] = VisualPointer(isAbovePointer, temp_name_rect, temp_arrow_rect, 
                                                        font_ptr, renderer_ptr, name, name_texture_ptr);
    currentPointerIndex++;
    SDL_FreeSurface(temp_surface);
}

void VisualArray::setComparing(index_t index1, index_t index2, bool boolean)
{
    visualArray[index1].setComparing(boolean);
    visualArray[index2].setComparing(boolean);
}

void VisualArray::swapElementsInArray(index_t index1, index_t index2)
{
    VisualNumber temp;
    temp = visualArray[index1];
    visualArray[index1] = visualArray[index2];
    visualArray[index2] = temp;
}

void VisualArray::swap(index_t index1, index_t index2, Configuration* config_ptr)
{
    SDL_Renderer* renderer_ptr = config_ptr->renderer_ptr;
    SDL_Event* event_ptr = config_ptr->event_ptr;
    VisualArray* visualArray_ptr = config_ptr->visualArray_ptr;
    visualArray[index1].skipRender();
    visualArray[index2].skipRender();

    int index1_initial_x = initial_digit_rect.x + index1*RED_SQUARE_WIDTH;
    int index1_current_x = index1_initial_x;
    int index2_x         = initial_digit_rect.x + index2*RED_SQUARE_WIDTH;
    int index2_current_x = index2_x;
    int increment        = index1 - index2;
    SDL_Rect temp_rect;
    temp_rect.w = initial_digit_rect.w;
    temp_rect.h = initial_digit_rect.h; 
    temp_rect.y = initial_digit_rect.y;
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
        for(int i = 0; i < SPEED && index1_current_x != index2_x; i++)
        {
            index1_current_x-= increment;
            index2_current_x+= increment;
        }

        SDL_RenderClear(renderer_ptr);
        temp_rect.x = index1_current_x;
        SDL_RenderCopy(renderer_ptr, visualArray[index1].getTexture(), NULL, &temp_rect);
        temp_rect.x = index2_current_x;
        SDL_RenderCopy(renderer_ptr, visualArray[index2].getTexture(), NULL, &temp_rect);
        visualArray_ptr->renderArray();
        SDL_RenderPresent(renderer_ptr);
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
    initial_digit_rect =  V.initial_digit_rect;
    renderer_ptr = V.renderer_ptr;
    for(unsigned int i = 0; i < size; i++)
    {
        visualArray[i] = V.visualArray[i];
    }
    for(unsigned int i = 0; i < pointersSize; i++)
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