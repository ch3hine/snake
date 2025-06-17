#include "UIManager.h"

UIManager::UIManager(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->score = 0;
}

void UIManager::Draw()
{
    SDL_Color color = {255, 255, 255, 100}; // blanc

    std::string text = "Score : " + std::to_string(score);

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // plus besoin du surface
    SDL_Rect dstRect = {20, 20, surface->w, surface->h}; // position du texte
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect); // dessine le texte
    SDL_DestroyTexture(texture); // libère la texture après affichage
}

void UIManager::setFont(TTF_Font* font)
{
    this->font = font;
}

void UIManager::IncrementScore(int num)
{
    score += num;
}

void UIManager::ResetScore()
{
    score = 0;
}

UIManager::~UIManager()
{
    delete this;
}