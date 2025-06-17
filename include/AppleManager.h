#pragma once

#include <SDL.h>
#include "Apple.h"
#include <vector>
#include <algorithm>

class AppleManager
{
public:
    AppleManager(SDL_Renderer* renderer);
    void generateApples();
    void Draw();
    std::vector<Apple>& getApples() {return _apples;}

private:
    SDL_Renderer* _renderer;
    std::vector<Apple> _apples;

};