#pragma once

class VisualArray;
class VisualPointer;
struct Configuration;
#include "VisualNumber.hpp"
#include "VisualPointer.hpp"
#include "Globals.hpp"
#include <iostream>
#include <string>

class VisualArray
{
public:
    VisualArray(const int array[], const unsigned int size, const unsigned int pointersSize, 
                SDL_Rect initial_digit_rect, 
                SDL_Renderer* renderer_ptr,
                TTF_Font* font_ptr);
    void split();
    void swapElementsPointedBy(std::string pointer1, std::string pointer2, Configuration* config_ptr);
    void swap(const index_t index1, const index_t index2, Configuration* config_ptr);
    void slidePointer(std::string name, const index_t _index, Configuration* config_ptr);
    void slidePointer(std::string name, std::string name2, Configuration* config_ptr);
    void incrementPointer(std::string name, Configuration* config_ptr);
    void decrementPointer(std::string name, Configuration* config_ptr);
    void setComparing(const index_t index1, const index_t index2, bool boolean);
    void renderArray();
    VisualPointer* getPointer(std::string name);
    VisualPointer* getPointer(const index_t index);
    int getVal(const index_t index);
    void addPointer(bool isAbovePointer, const index_t index, TTF_Font* font_ptr, std::string name);
    void destroy();
    void operator=(const VisualArray& V);
private:
    void swapElementsInArray(const index_t index1, const index_t index2);
    void renderPointers();    
    unsigned int size;
    unsigned int pointersSize;
    unsigned int currentPointerIndex;
    unsigned int single_digit_width;
    unsigned int double_digit_width;
    SDL_Texture* red_square_texture_ptr;
    SDL_Rect initial_digit_rect;
    SDL_Renderer* renderer_ptr;
    VisualNumber* visualArray;
    VisualPointer* visualPointers;
};