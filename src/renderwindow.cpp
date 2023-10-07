/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow()
    :renderer(NULL), window(NULL)
{

}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
    {   std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;  }

    return texture;
}

void RenderWindow::render(Entity& p_entity)
{
    SDL_Rect src;
    src.x = p_entity.getCurrentFrame().x;
    src.y = p_entity.getCurrentFrame().y;
    src.w = p_entity.getCurrentFrame().w;
    src.h = p_entity.getCurrentFrame().h;

    SDL_Rect dst;
    dst.x = p_entity.getX();
    dst.y = p_entity.getY();
    dst.w = p_entity.getCurrentFrame().w;
    dst.h = p_entity.getCurrentFrame().h;

    SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dst);

}
*/