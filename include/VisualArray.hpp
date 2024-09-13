#pragma once

class VisualArray;
class VisualPointer;
class VisualVariable;
struct Configuration;
#include "VisualNumber.hpp"
#include "VisualPointer.hpp"
#include "VisualVariable.hpp"
#include "Globals.hpp"
#include <iostream>
#include <string>

class VisualArray
{
public:
    VisualArray(const int array[], const unsigned short size, const unsigned short pointersSize, 
                SDL_Rect initial_digit_rect, 
                SDL_Renderer* renderer_ptr,
                TTF_Font* font_ptr,
                unsigned short font_size,
                const short window_height,
                const short window_width);
    void swapElementsPointedBy(std::string pointer1, std::string pointer2, Configuration* config_ptr);
    void swap(const int index1, const int index2, Configuration* config_ptr);
    void insert(VisualNumber* inserted, int inserted_into_index, Configuration* config_ptr);
    void insert(int inserted_index, int inserted_into_index, Configuration* config_ptr);
    void slidePointer(std::string name, const int _index, Configuration* config_ptr);
    void slidePointer(std::string name, std::string name2, Configuration* config_ptr);
    void incrementPointer(std::string name, Configuration* config_ptr);
    void decrementPointer(std::string name, Configuration* config_ptr);
    void setComparing(const int index1, const int index2, bool boolean);
    void setComparing(int index, std::string variable_name, bool boolean);
    void setComparing(std::string variable_1_name, std::string variable_2_name, bool boolean);
    void renderCopyArray();
    void renderCopySquaresAndNumbers();
    void renderCopyInfo(std::string info);
    VisualPointer* getPointer(std::string name);
    VisualPointer* getPointer(const int index);
    int getVal(const int index);
    VisualVariable* getVariable(std::string name);
    void addVariable(std::string name, const int value);
    void updateVariable(std::string name, const int value);
    void addPointer(bool isAbovePointer, const int index, TTF_Font* font_ptr, std::string name);
    void destroy();
    void operator=(const VisualArray& V);
private:
    void swapElementsInArray(const int index1, const int index2);
    void renderCopyPointers();    
    void renderCopyVariables(SDL_Renderer* renderer_ptr, const unsigned short height, const unsigned short width);
    unsigned short size;
    unsigned short pointersSize;
    unsigned short currentPointerIndex;
    unsigned short swaps;
    unsigned short insertions;
    unsigned short comparisons;
    unsigned short font_size;
    unsigned short window_height;
    unsigned short window_width;
    unsigned short number_of_variables;
    unsigned short time_counter;
    VisualVariable visualVariables[4]; // grow as needed
    SDL_Texture* red_square_texture_ptr;
    SDL_Rect initial_digit_rect;
    SDL_Renderer* renderer_ptr;
    TTF_Font* font_ptr;
    TTF_Font* small_font_ptr;
    VisualNumber* visualArray;
    VisualPointer* visualPointers;
};