#include "environnement.h"

Environnement::Environnement(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

void Environnement::Draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // vert

    int thickness = 10; // épaisseur du contour
    int width = 1000;   // largeur de la fenêtre
    int height = 1000;  // hauteur de la fenêtre

    SDL_Rect top    = { 0, 0, width, thickness };
    SDL_Rect bottom = { 0, height - thickness, width, thickness };
    SDL_Rect left   = { 0, 0, thickness, height };
    SDL_Rect right  = { width - thickness, 0, thickness, height };

    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);
    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);

}

Environnement::~Environnement()
{
    delete this;
}