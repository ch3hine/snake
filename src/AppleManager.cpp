#include "AppleManager.h"

AppleManager::AppleManager(SDL_Renderer* renderer)
{
    _renderer = renderer;

}

void AppleManager::generateApples()
{
    _apples.clear();
    for (int i = 0; i < 1; i++)
    {
        SDL_Color color = {255, 0,0,255};

        int chance = rand() % 100 + 1; // entre 1 et 100 inclus

        if (chance <= 50) {
            // Rouge (50%)
            color = {255, 0, 0, 255};
        } else if (chance <= 80) {
            // Vert (30%)
            color = {0, 255, 0, 255};
        } else {
            // Jaune (20%)
            color = {255, 255, 0, 255};
        }

        SDL_Rect rect = {
            (rand() % 98) * 10 + 10,
            (rand() % 98) * 10 + 10,
            10,
            10
        };

        _apples.emplace_back(this->_renderer, color, rect);
    }

}

void AppleManager::Draw()
{
    std::for_each(_apples.begin(), _apples.end(), [&](Apple &apple)
                    { apple.Draw(); });
}

// for (int i = 0; i < 1; i++)
//     {
//         _apples.emplace_back(rand() % 100 * 10, rand() % 100 * 10, 10, 10);
//     }

