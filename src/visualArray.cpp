#include "VisualArray.hpp"
#include "Globals.hpp"

void destroyVisualSort(Configuration* config);

void alignSquareWithNumber(SDL_Rect* number_rect_ptr, SDL_Rect* square_rect_ptr);

VisualArray::VisualArray(const int array[], const unsigned int size, const unsigned int pointersSize, 
                        SDL_Rect initial_digit_rect, 
                        SDL_Renderer* renderer_ptr,
                        TTF_Font* font_ptr,
                        const unsigned int font_size,
                        const int window_height,
                        const int window_width)
{
    currentPointerIndex = 0;
    this->size =                   size;
    this->initial_digit_rect =     initial_digit_rect;
    this->red_square_texture_ptr = IMG_LoadTexture(renderer_ptr, "textures/red_square.png");
    this->renderer_ptr =           renderer_ptr;
    this->pointersSize =           pointersSize;
    this->swaps =                  0;
    this->insertions =             0;
    this->comparisons =            0;
    this->font_ptr =               font_ptr;
    this->font_size =              font_size;
    this->window_height =          window_height;
    this->window_width =           window_width;
    this->number_of_variables =    0;
    this->time_counter =           0;

    this->small_font_ptr =         TTF_OpenFont("Rubik-Regular.ttf", INITIAL_FONT_SIZE / 2);
    if (small_font_ptr == NULL)
    {
        std::cout << "Error opening font: " << SDL_GetError() << std::endl;
    } 
    SDL_Rect red_square_rect;
    alignSquareWithNumber(&initial_digit_rect, &red_square_rect);
    this->red_square_rect.x = red_square_rect.x;
    this->red_square_rect.y = red_square_rect.y;
    this->red_square_rect.w = red_square_rect.w;
    this->red_square_rect.h = red_square_rect.h;

    visualArray = new VisualNumber[size];
    for(unsigned int i = 0; i < size; i++)
    {
        this->visualArray[i] = VisualNumber(array[i], font_ptr, &(this->red_square_rect), renderer_ptr);
    }
    visualPointers = new VisualPointer[pointersSize];
}

void alignSquareWithNumber(SDL_Rect* number_rect_ptr, SDL_Rect* square_rect_ptr)
{
    square_rect_ptr->w      = RED_SQUARE_WIDTH;
    square_rect_ptr->h      = square_rect_ptr->w;
    square_rect_ptr->x      = number_rect_ptr->x - DOUBLE_DIGIT_WIDTH/2;
    int number_center       = number_rect_ptr->y + number_rect_ptr->h/2;
    square_rect_ptr->y      = number_center - DOUBLE_DIGIT_WIDTH;
}

void VisualArray::renderArray()
{
    std::string info_string = "Comparisons: " + std::to_string(comparisons) + " | ";
    info_string += "Swaps: " + std::to_string(swaps) + " | ";
    info_string += "Insertions: " + std::to_string(insertions);
    

    renderCopyInfo(info_string);
    renderCopySquaresAndNumbers();
    renderCopyPointers();
    renderCopyVariables(renderer_ptr, window_height, window_width);
}

void VisualArray::renderCopySquaresAndNumbers()
{
    SDL_Rect number_rect;
    number_rect.x = initial_digit_rect.x;
    number_rect.y = initial_digit_rect.y;
    number_rect.h = initial_digit_rect.h;
    number_rect.w = -1;
    //width is set later because it depends on number of digits
    alignSquareWithNumber(&initial_digit_rect, &red_square_rect);
    for(unsigned int i = 0; i < size; i++)
    {
        visualArray[i].renderCopy(&time_counter, 
                                  &number_rect, red_square_texture_ptr, renderer_ptr);
        SDL_RenderCopy(renderer_ptr, red_square_texture_ptr, NULL, &red_square_rect);
        number_rect.x += RED_SQUARE_WIDTH;
        red_square_rect.x += RED_SQUARE_WIDTH;
    }
}

void VisualArray::renderCopyInfo(std::string info){
    
    SDL_Surface* info_surface = TTF_RenderText_Solid(small_font_ptr, info.c_str(), WHITE);
    if (info_surface == NULL){
        std::cout << "Error:" << TTF_GetError() << std::endl;
    }
    SDL_Texture* info_texture = SDL_CreateTextureFromSurface(renderer_ptr, info_surface);
    
    SDL_Rect info_rect;
    info_rect.w = info_surface->w;
    info_rect.h = info_surface->h;
    info_rect.x = window_width/2 - info_rect.w/2;
    info_rect.y = window_height - info_rect.h;    

    SDL_RenderCopy(renderer_ptr, info_texture, NULL, &info_rect);
    SDL_FreeSurface(info_surface);
}

void VisualArray::renderCopyPointers()
{
    for(index_t i = 0; i < currentPointerIndex; i++)
    {
        visualPointers[i].render(renderer_ptr);
    }
}

void VisualArray::renderCopyVariables(SDL_Renderer* renderer_ptr, 
                                  const unsigned int height, const unsigned int width)
{
    for(unsigned int i = 0; i < number_of_variables; i++)
    {
        visualVariables[i].render(renderer_ptr, height, width, font_ptr, &time_counter);
    }
}

int VisualArray::getVal(index_t index)
{
    return visualArray[index].getValue();
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

    //std::cout << "failed to find pointer named " << name << std::endl;
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
    temp_name_rect.x = initial_digit_rect.x + RED_SQUARE_WIDTH * index + DOUBLE_DIGIT_WIDTH/2 - temp_surface->w/2;

    SDL_Rect temp_arrow_rect;
    temp_arrow_rect.w = DOUBLE_DIGIT_WIDTH * 1.25;
    temp_arrow_rect.h = DOUBLE_DIGIT_WIDTH * 1.25;
    temp_arrow_rect.x = initial_digit_rect.x + RED_SQUARE_WIDTH * index - temp_arrow_rect.w/2 + DOUBLE_DIGIT_WIDTH/2;

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
                                                        font_ptr, renderer_ptr, name, name_texture_ptr,
                                                        index);
    currentPointerIndex++;
    SDL_FreeSurface(temp_surface);
}

void VisualArray::addVariable(std::string name, const int value)
{
    visualVariables[number_of_variables++] = VisualVariable(name, value, font_ptr, &red_square_rect, renderer_ptr);
}

VisualVariable* VisualArray::getVariable(std::string name)
{  
    for(index_t i = 0; i < number_of_variables; i++)
    {
        if(visualVariables[i].getName() == name)
        {
            return &visualVariables[i];
        }
    }

    std::cout << "failed to find variable named " << name << std::endl;
    return NULL;
}

void VisualArray::updateVariable(std::string name, const int value)
{
    getVariable(name)->setValue(value, font_ptr, renderer_ptr);
}

void VisualArray::setComparing(index_t index1, index_t index2, bool boolean)
{
    if(boolean == true) {  comparisons++;  }
    time_counter = 0;
    visualArray[index1].setComparing(boolean);
    visualArray[index2].setComparing(boolean);
}

void VisualArray::setComparing(index_t index, std::string variable_name, bool boolean)
{
    //if(boolean == true) {  comparisons++;  } decide on this later
    time_counter = 0;
    visualArray[index].setComparing(boolean);
    getVariable(variable_name)->setComparing(boolean);
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
    swaps++;
    SDL_Renderer* renderer_ptr = config_ptr->renderer_ptr;
    SDL_Event* event_ptr = config_ptr->event_ptr;
    VisualArray* visualArray_ptr = config_ptr->visualArray_ptr;
    visualArray[index1].setSkipRender(true);
    visualArray[index2].setSkipRender(true);

    int index1_x         = initial_digit_rect.x + index1*RED_SQUARE_WIDTH;
    int index2_x         = initial_digit_rect.x + index2*RED_SQUARE_WIDTH;
    int increment        = index1 - index2;

    SDL_Rect index_1_rect;
    if (visualArray[index1].getValue() < 10){
        index_1_rect.w = SINGLE_DIGIT_WIDTH;
    }  else {
        index_1_rect.w = DOUBLE_DIGIT_WIDTH;
    }
    index_1_rect.h = initial_digit_rect.h; 
    index_1_rect.y = initial_digit_rect.y;
    index_1_rect.x = index1_x;

    SDL_Rect index_2_rect;
    if (visualArray[index2].getValue() < 10){
        index_2_rect.w = SINGLE_DIGIT_WIDTH;
    }  else {
        index_2_rect.w = DOUBLE_DIGIT_WIDTH;
    }
    index_2_rect.h = initial_digit_rect.h; 
    index_2_rect.y = initial_digit_rect.y;
    index_2_rect.x = index2_x;

    while(index_1_rect.x != index2_x)
    {
        while (SDL_PollEvent(event_ptr))
        {
            if (event_ptr->type == SDL_QUIT)
            {
                destroyVisualSort(config_ptr);
            }
        }
        for(int i = 0; i < SPEED && index_1_rect.x != index2_x; i++)
        {
            index_1_rect.x-= increment;
            index_2_rect.x+= increment;
        }

        SDL_RenderClear(renderer_ptr);
        SDL_RenderCopy(renderer_ptr, visualArray[index1].getTexture(), NULL, &index_1_rect);
        SDL_RenderCopy(renderer_ptr, visualArray[index2].getTexture(), NULL, &index_2_rect);
        visualArray_ptr->renderArray();
        SDL_RenderPresent(renderer_ptr);
    } 
    visualArray[index1].setSkipRender(false);
    visualArray[index2].setSkipRender(false); 
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