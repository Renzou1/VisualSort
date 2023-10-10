#include <VisualPointer.hpp>
#include <VisualArray.hpp>
#include <Globals.hpp>

VisualPointer::VisualPointer()
:name("i"), index(0), isAbovePointer(true), name_texture_ptr(NULL), arrow_texture_ptr(NULL)
{}

VisualPointer::VisualPointer(bool isAbovePointer, SDL_Rect name_rect, SDL_Rect arrow_rect, 
                            TTF_Font* font_ptr, SDL_Renderer* renderer_ptr, std::string name)
{
    SDL_Color white = {255, 255, 255};
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font_ptr, name.c_str(), white);
    name_texture_ptr = SDL_CreateTextureFromSurface(renderer_ptr, temp_surface);
    this->name_rect.w = temp_surface->w;
    this->name_rect.h = temp_surface->h;
    this->name_rect.y = name_rect.y;
    this->name_rect.x = name_rect.x;
    SDL_FreeSurface(temp_surface);
    this->isAbovePointer = isAbovePointer;
    if(isAbovePointer)
    {  arrow_texture_ptr = IMG_LoadTexture(renderer_ptr, "resources/down_arrow.png");  }
        else
    {  arrow_texture_ptr = IMG_LoadTexture(renderer_ptr, "resources/up_arrow.png");  }
    this->name = name;
    //this->name_rect = name_rect;
    this->arrow_rect = arrow_rect;
    this->index = 0;
}

int VisualPointer::getIndex()
{  return this->index;  }

std::string VisualPointer::getName()
{  return this->name;  }

bool VisualPointer::slidePointer(int _index, SDL_Renderer* renderer_ptr, VisualArray* visualArray_ptr,
                                SDL_Event* event_ptr)
{
    int initial_x = name_rect.x;
    int distanceToIndex = _index - index;
    int increment = _index - index;
    int goal_x = initial_x + distanceToIndex * DISTANCE;
    
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
            SDL_Delay(10 / SPEED);
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
            SDL_Delay(10 / SPEED);
        }
    }*/


}

void VisualPointer::render(SDL_Renderer* renderer_ptr)
{
    SDL_RenderCopy(renderer_ptr, name_texture_ptr, NULL, &name_rect);
    SDL_RenderCopy(renderer_ptr, arrow_texture_ptr, NULL, &arrow_rect);
}

void VisualPointer::destroy()
{
    SDL_DestroyTexture(name_texture_ptr);
    SDL_DestroyTexture(arrow_texture_ptr);
}