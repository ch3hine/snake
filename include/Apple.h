#pragma once

#include <SDL.h>

class Apple
{
public:
    SDL_Color _color;
    SDL_Renderer* _renderer;
    SDL_Rect _rect;

    Apple(SDL_Renderer* renderer, SDL_Color _color, SDL_Rect rect);
    void Draw();

};