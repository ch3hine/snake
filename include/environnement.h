#pragma once

#include <SDL.h>

class Environnement
{
public:
    Environnement(SDL_Renderer* renderer); 
    ~Environnement();

    void Draw();
private:
    SDL_Renderer* renderer;
};