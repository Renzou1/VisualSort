#pragma once

class VisualArray;
class VisualPointer;
struct Configuration;
#include "VisualNumber.hpp"
#include "VisualPointer.hpp"
#include <iostream>
#include <string>

class VisualArray
{
public:
    VisualArray(int array[], int size, int pointersSize, 
                SDL_Rect* first_rect_ptr, 
                SDL_Renderer* renderer_ptr,
                TTF_Font* font_ptr);
    void split();
    void swapElements(int index1, int index2);
    bool swap(int index1, int index2, Configuration config);
    bool slidePointer(std::string name, int _index, Configuration config);
    bool incrementPointer(std::string name, Configuration config);
    bool decrementPointer(std::string name, Configuration config);
    void renderArray();
    void renderPointers();
    VisualPointer* getPointer(std::string name);
    VisualPointer* getPointer(int index);
    int getVal(int index);
    void addPointer(bool isAbovePointer, int index, TTF_Font* font_ptr, std::string name);
    void destroy();
private:
    int size;
    int currentPointerIndex;
    SDL_Texture* red_square_texture_ptr;
    SDL_Rect* first_rect_ptr;
    SDL_Renderer* renderer_ptr;
    VisualNumber* visualArray;
    VisualPointer* visualPointers;
};