#pragma once

#define INITIAL_FONT_SIZE 80 // best through experimentation: 80 
#define ARROW_TEXTURE_OFFSET -50
#define ARROW_DISTANCE_MULTIPLIER 1.5
#define INDEX_TEXTURE_OFFSET 22
#define DISTANCE_TO_TOP_OF_SCREEN 250
#define RED_SQUARE_WIDTH 2 * double_digit_width
#define SPEED 2
#define WAIT_FOR_INPUT 0
#define SELECTION_SORT 1
#define INSERTION_SORT 2
#define MERGE_SORT     3
#define QUICK_SORT     4

typedef unsigned int index_t;
const SDL_Color WHITE = {255, 255, 255};