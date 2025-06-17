#include "Apple.h"

Apple::Apple(SDL_Renderer* renderer, SDL_Color color, SDL_Rect rect)
{
    _renderer = renderer;
    _color = color;
    _rect = rect;
}

void Apple::Draw()
{
    SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(_renderer, &_rect);
}