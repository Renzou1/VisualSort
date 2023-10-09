#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class VisualPointer
{
public:
    VisualPointer();
    VisualPointer(bool isAbovePointer, SDL_Rect name_rect, SDL_Rect arrow_rect,
                    TTF_Font* font_ptr, SDL_Renderer* renderer_ptr, std::string name);
    void render(SDL_Renderer* renderer_ptr);
    void destroy();
private:
    std::string name;
    int index;
    bool isAbovePointer;
    SDL_Texture* name_texture_ptr;
    SDL_Texture* arrow_texture_ptr;
    SDL_Rect name_rect;
    SDL_Rect arrow_rect;
};