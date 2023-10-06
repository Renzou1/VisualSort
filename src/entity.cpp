#include "Entity.hpp"

Entity::Entity(float p_x, float p_y, SDL_Texture*  p_tex)
:x(p_x), y(p_y), texture(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 225;
    currentFrame.h = 225;
}

float Entity::getX()
{
    return x;
}

float Entity::getY()
{
    return y;
}

void Entity::xpp()
{
    x = x + 1;
}

SDL_Texture* Entity::getTexture()
{
    return texture;
}

SDL_Rect Entity::getCurrentFrame()
{
    return currentFrame;
}