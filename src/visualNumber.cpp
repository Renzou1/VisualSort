#include <VisualNumber.hpp>
#include <iostream>

VisualNumber::VisualNumber()
:val(0), skipRender(false), isComparing_(false), isComparingFlag2_(0), number_texture(NULL)
{}

VisualNumber::VisualNumber(int val, TTF_Font* font_ptr, SDL_Renderer* renderer_ptr)
{
    this->val = val;
    //create number texture:
    SDL_Color white = {255, 255, 255};
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font_ptr, std::to_string(val).c_str(), white);
    number_texture = SDL_CreateTextureFromSurface(renderer_ptr, temp_surface);
    SDL_FreeSurface(temp_surface);
    this->skipRender = false;
}

SDL_Texture* VisualNumber::getTexture()
{  return number_texture;  }

bool VisualNumber::getSkipRender()
{  return skipRender;  }

void VisualNumber::setSkipRender(bool _skipRender)
{  skipRender = _skipRender;  }

int VisualNumber::getVal()
{  return val;  }

bool VisualNumber::isComparing()
{  return isComparing_;  }

void VisualNumber::setComparing(bool param)
{  
    isComparing_ = param;
    if(param == false)
    {
        isComparingFlag2_ = 0;
    }
}

int VisualNumber::getFlag2()
{  return isComparingFlag2_;  }

void VisualNumber::incrementFlag2()
{  isComparingFlag2_++;  }

void VisualNumber::resetFlag2()
{  isComparingFlag2_ = 0;  }

void VisualNumber::operator=(const VisualNumber& V)
{
    val = V.val;
    skipRender = V.skipRender;
    number_texture = V.number_texture;
}

void VisualNumber::destroy()
{  SDL_DestroyTexture(number_texture);  }

