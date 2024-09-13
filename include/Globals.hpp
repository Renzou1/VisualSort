#pragma once

#define INITIAL_FONT_SIZE 80 // best through experimentation: 80 
#define ARROW_TEXTURE_OFFSET -50
#define ARROW_DISTANCE_MULTIPLIER 1.5
#define INDEX_TEXTURE_OFFSET 22
#define DISTANCE_TO_TOP_OF_SCREEN 350 //250
#define RED_SQUARE_WIDTH (2 * DOUBLE_DIGIT_WIDTH)
#define SPEED 3
#define DEFAULT_DELAY 200
#define WAIT_FOR_INPUT 1
#define SELECTION_SORT 1
#define INSERTION_SORT 2
#define MERGE_SORT     3
#define QUICK_SORT     4
#define FONT_PATH "/home/renzo/vscodeprojects/VisualSort/Rubik-Regular.ttf"

const SDL_Color WHITE = {255, 255, 255};

extern unsigned int SINGLE_DIGIT_WIDTH;
extern unsigned int DOUBLE_DIGIT_WIDTH;
extern unsigned int TEXT_HEIGHT;