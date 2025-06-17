#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class Button
{
public:
    Button(SDL_Renderer* renderer);
    ~Button();

    void setColor(SDL_Color color);
    void setTextColor(SDL_Color color);
    void setLabel(std::string label);
    void setFont(std::string fontName, int size);
    void setPosition(int x, int y);
    void setSize(int w, int h);

    void handleInput(SDL_Event& event);
    bool isCLicked(int mouseX, int mouseY)const;

    void Draw();


private:
    SDL_Rect        _rect;
    SDL_Color       _color;
    std::string     _label;
    SDL_Color       _text_color;
    TTF_Font*       _font;
    SDL_Renderer*   _renderer;
};