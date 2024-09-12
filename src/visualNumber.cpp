#include <VisualNumber.hpp>
#include <iostream>

VisualNumber::VisualNumber()
:value(0), skipRender(false), isComparing(false), texture(NULL)
{}

SDL_Texture* createTextureFromValue(const int value, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr)
{
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font_ptr, std::to_string(value).c_str(), WHITE);
    SDL_Texture* texture_ptr = SDL_CreateTextureFromSurface(renderer_ptr, temp_surface);
    SDL_FreeSurface(temp_surface);    
    return texture_ptr;
}

VisualNumber::VisualNumber(int value, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr)
{
    this->value = value;
    this->texture = createTextureFromValue(value, font_ptr, renderer_ptr);
    this->skipRender = false;
    this->x = 0;
    this->y = 0;
}

SDL_Texture* VisualNumber::getTexture()
{  return texture;  }

bool VisualNumber::shouldSkipRender()
{  return skipRender;  }

void VisualNumber::setSkipRender(bool _skipRender)
{  skipRender = _skipRender;  }

int VisualNumber::getValue()
{  return value;  }

void VisualNumber::setValue(const int value_, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr)
{
    value = value_;
    texture = createTextureFromValue(value, font_ptr, renderer_ptr);
}

bool VisualNumber::getIsComparing()
{  return isComparing;  }

void VisualNumber::setComparing(bool param)
{  
    isComparing = param;
}

void VisualNumber::operator=(const VisualNumber& V)
{
    value = V.value;
    skipRender = V.skipRender;
    texture = V.texture;
}

void VisualNumber::destroy()
{  SDL_DestroyTexture(texture);  }

void VisualNumber::renderCopy(unsigned int* time_counter,
                              SDL_Rect* number_rect_ptr,
                              SDL_Texture* red_square_texture_ptr,
                              SDL_Renderer* renderer_ptr)
{
    number_rect_ptr->h = TEXT_HEIGHT;
    this->x = number_rect_ptr->x;
    this->y = number_rect_ptr->y;
    if(skipRender == false)
    {
        if(value >= 10)
        {  
            number_rect_ptr->w = DOUBLE_DIGIT_WIDTH;  
            SDL_RenderCopy(renderer_ptr, texture, NULL, number_rect_ptr);

        }  else
        {  
            number_rect_ptr->w = SINGLE_DIGIT_WIDTH;

            int difference_in_centers = DOUBLE_DIGIT_WIDTH/2 - SINGLE_DIGIT_WIDTH/2;
            
            number_rect_ptr->x += difference_in_centers;
            SDL_RenderCopy(renderer_ptr, texture, NULL, number_rect_ptr);
            number_rect_ptr->x -= difference_in_centers;
        }
            
    }
    if(isComparing) // tied to refresh rate I think, bad
    {
        unsigned int time = 240;
        if(*time_counter < time/2)
        {
            SDL_Rect compare_square_rect;
            compare_square_rect.w = RED_SQUARE_WIDTH*0.8;
            compare_square_rect.h = RED_SQUARE_WIDTH*0.8;

            int number_center       = number_rect_ptr->y + number_rect_ptr->h/2;

            int length_difference = RED_SQUARE_WIDTH - compare_square_rect.w;
            compare_square_rect.x = number_rect_ptr->x - DOUBLE_DIGIT_WIDTH/2 + (length_difference/2);
            compare_square_rect.y = number_center - DOUBLE_DIGIT_WIDTH + (length_difference/2);

            SDL_RenderCopy(renderer_ptr, red_square_texture_ptr, NULL, &compare_square_rect);
        }  else if (*time_counter > time)
        {  *time_counter = 0;  }

        (*time_counter)++;
    }
}