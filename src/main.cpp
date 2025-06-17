#include <SDL.h>
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
#include <SDL_ttf.h>
#include "snake.h"
#include "UIManager.h"
#include "environnement.h"
#include "AppleManager.h"
#include "Button.h"
#include <SDL_image.h>


void renderBackground(SDL_Renderer* renderer, int screenWidth, int screenHeight, int cellSize)
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100); // Gris clair pour la grille

    // Lignes verticales
    for (int x = 0; x <= screenWidth; x += cellSize)
    {
        SDL_RenderDrawLine(renderer, x, 0, x, screenHeight);
    }

    // Lignes horizontales
    for (int y = 0; y <= screenHeight; y += cellSize)
    {
        SDL_RenderDrawLine(renderer, 0, y, screenWidth, y);
    }
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "TTF_Init Error : " << TTF_GetError() << std::endl;
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("font/chilispepper.ttf", 24); // Chemin vers la police et taille
    if (!font)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Snake-SDL2",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1000, 1000,
                                          SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Surface* icon = IMG_Load("assets/snake_logo.png");
    if (icon) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    //* NEW CLASS SNAKE PARAMS
    Environnement env(renderer);
    AppleManager apple(renderer);
    Snake snake(renderer);
    UIManager uimanager(renderer);
    uimanager.setFont(font);

    snake.setCallback(
        [&uimanager]()
        { uimanager.ResetScore(); }, [&uimanager](int amount)
        {
            uimanager.IncrementScore(amount);
        },
        [&apple]()
        { apple.generateApples(); });

    bool running = true;
    SDL_Event event;

    apple.generateApples();

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            snake.handleInput(event);
        }

        //* Move
        snake.move();

        //* Collision detection
        snake.handleCollisions(apple.getApples());

        //* Add newest head to snake
        snake.updateSnake();

        //* Clear Window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //* Draw (based on z-index)
        int cellSize = 10;

        renderBackground(renderer, 1000, 1000, cellSize);
        snake.Draw();
        apple.Draw();
        env.Draw();
        uimanager.Draw();

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
