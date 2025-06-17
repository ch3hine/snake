#pragma once

#include <SDL.h>
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
#include <functional>
#include "Apple.h"


enum Direction
{
    STOPPED,
    DOWN,
    LEFT,
    RIGHT,
    UP
};

class Snake
{
public:
    Snake(SDL_Renderer* renderer);
    ~Snake();

    void move();
    void handleInput(SDL_Event& event);
    void handleCollisions(std::vector<Apple>& apples);
    void setCallback(std::function<void()> lose, std::function<void(int)> addPoint, std::function<void()> generateApples);
    void updateSnake();
    void Draw();
    
private:
    void handleSelfCollisions();
    void handleApplesCollisions(std::vector<Apple> &apples);
    void handleEnvironnementCollision();
    void handleLoose();
    
    std::deque<SDL_Rect> snake_body;
    int current_direction;
    int last_direction;
    int snake_size;

    //* Callback

    std::function<void()> loseCallback;
    std::function<void(int)> addPointCallback;
    std::function<void()> generateApplesCallback;

    //* Rendering
    SDL_Rect snake_head;
    SDL_Renderer* renderer;
};