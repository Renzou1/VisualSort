#include <VisualPointer.hpp>

VisualPointer::VisualPointer()
{

}

VisualPointer::VisualPointer(bool isAbovePointer, SDL_Rect name_rect, SDL_Rect arrow_rect, 
                            TTF_Font* font_ptr, SDL_Renderer* renderer_ptr, std::string name)
{
    SDL_Color white = {255, 255, 255};
    SDL_Surface* temp_surface = TTF_RenderText_Solid(font_ptr, name.c_str(), white);
    name_texture_ptr = SDL_CreateTextureFromSurface(renderer_ptr, temp_surface);
    SDL_FreeSurface(temp_surface);
    this->isAbovePointer = isAbovePointer;
    this->name = name;
    this->name_rect = name_rect;
    this->arrow_rect = arrow_rect;
    this->arrow_texture_ptr = IMG_LoadTexture(renderer_ptr, "resources/arrow.png");

}

void VisualPointer::render(SDL_Renderer* renderer_ptr)
{
    SDL_RenderCopy(renderer_ptr, name_texture_ptr, NULL, &name_rect);
    SDL_RenderCopy(renderer_ptr, arrow_texture_ptr, NULL, &arrow_rect);
}

void VisualPointer::destroy()
{
    SDL_DestroyTexture(name_texture_ptr);
    SDL_DestroyTexture(arrow_texture_ptr);
}