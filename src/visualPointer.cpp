#include <VisualPointer.hpp>
#include <VisualArray.hpp>
#include <Globals.hpp>

VisualPointer::VisualPointer()
:name("i"), index(0), isAbovePointer(true), name_texture_ptr(NULL), arrow_texture_ptr(NULL)
{}

VisualPointer::VisualPointer(bool isAbovePointer, SDL_Rect name_rect, SDL_Rect arrow_rect, 
                            TTF_Font* font_ptr, SDL_Renderer* renderer_ptr, 
                            std::string name, SDL_Texture* name_texture_ptr)
{
    this->isAbovePointer = isAbovePointer;
    if(isAbovePointer)
    {  arrow_texture_ptr = IMG_LoadTexture(renderer_ptr, "textures/down_arrow.png");  }
        else
    {  arrow_texture_ptr = IMG_LoadTexture(renderer_ptr, "textures/up_arrow.png");  }
    this->name = name;
    this->name_texture_ptr = name_texture_ptr;
    this->name_rect = name_rect;
    this->arrow_rect = arrow_rect;
    this->index = 0;
}

int VisualPointer::getIndex()
{  return this->index;  }

std::string VisualPointer::getName()
{  return this->name;  }

bool VisualPointer::slidePointer(int _index, Configuration config)
{
    SDL_Renderer* renderer_ptr = config.renderer_ptr;
    SDL_Event* event_ptr = config.event_ptr;
    VisualArray* visualArray_ptr = config.visualArray_ptr;

    int initial_x = name_rect.x;
    int distanceToIndex = _index - index;
    int increment = _index - index;
    int goal_x = initial_x + distanceToIndex * config.double_digit_width*2;
    
    //if(_index > index)
    //{
        // kinda dangerous but maybe works
        while(name_rect.x != goal_x)
        {
            while (SDL_PollEvent(event_ptr))
            {
                if (event_ptr->type == SDL_QUIT)
                {
                    return false;
                }
            }
            name_rect.x+= increment; // speed is based on distance 
            arrow_rect.x+= increment;
            SDL_RenderClear(renderer_ptr);
            SDL_RenderCopy(renderer_ptr, name_texture_ptr, NULL, &name_rect);
            SDL_RenderCopy(renderer_ptr, arrow_texture_ptr, NULL, &arrow_rect);
            visualArray_ptr->renderArray();
            SDL_RenderPresent(renderer_ptr);
        }
        index = _index;
        return true;
    //}
    /*if(_index < index)
    {
        index = _index;
        while(name_rect.x > initial_x + distanceToIndex * DISTANCE)
        {
            name_rect.x--;
            arrow_rect.x--;
            SDL_RenderClear(renderer_ptr);
            SDL_RenderCopy(renderer_ptr, name_texture_ptr, NULL, &name_rect);
            SDL_RenderCopy(renderer_ptr, arrow_texture_ptr, NULL, &arrow_rect);
            visualArray_ptr->renderArray();
            SDL_RenderPresent(renderer_ptr);
        }
    }*/


}

void VisualPointer::render(SDL_Renderer* renderer_ptr)
{
    SDL_RenderCopy(renderer_ptr, name_texture_ptr, NULL, &name_rect);
    SDL_RenderCopy(renderer_ptr, arrow_texture_ptr, NULL, &arrow_rect);
}

void VisualPointer::operator=(const VisualPointer& V)
{
    name = V.name;
    index = V.index;
    isAbovePointer = V.isAbovePointer;
    name_texture_ptr = V.name_texture_ptr;
    arrow_texture_ptr = V.arrow_texture_ptr;
    name_rect = V.name_rect;
    arrow_rect = V.arrow_rect;
}

void VisualPointer::destroy()
{
    SDL_DestroyTexture(name_texture_ptr);
    SDL_DestroyTexture(arrow_texture_ptr);
}