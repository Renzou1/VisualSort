#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "VisualArray.hpp"
#include "Globals.hpp"
#include "configuration.hpp"

class VisualPointer
{
public:
    VisualPointer();
    VisualPointer(bool isAbovePointer, SDL_Rect name_rect, SDL_Rect arrow_rect, 
                            TTF_Font* font_ptr, SDL_Renderer* renderer_ptr, 
                            std::string name, SDL_Texture* name_texture_ptr,
                            int index);
    bool slidePointer(int _index, Configuration config, VisualArray* visualArray_ptr);
    int getIndex();
    void setIndex(const int _index)  {  index = _index;  }
    std::string getName();
    SDL_Rect* getNameRect() {  return &name_rect;  }
    SDL_Rect* getArrowRect() {  return &arrow_rect;  }
    SDL_Texture* getNameTexturePtr()  {  return name_texture_ptr;  }
    SDL_Texture* getArrowTexturePtr()  {  return arrow_texture_ptr;  }
    void renderCopy(SDL_Renderer* renderer_ptr);
    void destroy();
    void operator=(const VisualPointer& V);
private:
    std::string name;
    int index;
    bool isAbovePointer;
    SDL_Texture* name_texture_ptr;
    SDL_Texture* arrow_texture_ptr;
    SDL_Rect name_rect;
    SDL_Rect arrow_rect;
};