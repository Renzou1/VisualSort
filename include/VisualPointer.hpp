#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "VisualArray.hpp"

typedef struct Configuration
{
    SDL_Renderer* renderer_ptr;
    VisualArray* visualArray_ptr;
    SDL_Event* event_ptr;
}config;

class VisualPointer
{
public:
    VisualPointer();
    VisualPointer(bool isAbovePointer, SDL_Rect name_rect, SDL_Rect arrow_rect,
                    TTF_Font* font_ptr, SDL_Renderer* renderer_ptr, std::string name);
    bool slidePointer(int _index, Configuration config);
    int getIndex();
    void setIndex(int _index)  {  index = _index;  }
    std::string getName();
    SDL_Rect* getNameRect() {  return &name_rect;  }
    SDL_Rect* getArrowRect() {  return &arrow_rect;  }
    SDL_Texture* getNameTexturePtr()  {  return name_texture_ptr;  }
    SDL_Texture* getArrowTexturePtr()  {  return arrow_texture_ptr;  }
    void render(SDL_Renderer* renderer_ptr);
    void destroy();
private:
    std::string name;
    int index;
    bool isAbovePointer;
    SDL_Texture* name_texture_ptr;
    SDL_Texture* arrow_texture_ptr;
    SDL_Rect name_rect;
    SDL_Rect arrow_rect;
};