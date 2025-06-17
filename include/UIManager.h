#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>
#include <SDL_ttf.h>
#include <string>

class UIManager
{
public:
    UIManager(SDL_Renderer* renderer);
    ~UIManager();
    void setFont(TTF_Font* font);

    void IncrementScore(int num);
    void ResetScore();

    void Draw();
    
private:
    int score;
    SDL_Renderer* renderer;
    TTF_Font* font;
};