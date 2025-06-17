#include "Button.h"

Button::Button(SDL_Renderer* renderer)
{
    _renderer = renderer;
}

Button::~Button()
{

}

void Button::setColor(SDL_Color color)
{
    _color = color;
}

void Button::setTextColor(SDL_Color color)
{
    _text_color = color;
}

void Button::setLabel(std::string label)
{
    _label = label;
}

void Button::setFont(std::string fontName, int size)
{
    TTF_Font *font = TTF_OpenFont(fontName.c_str(), size); // Chemin vers la police et taille
    if (!font)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return;
    }

    _font = font;
}

void Button::setPosition(int x, int y)
{
    _rect.x = x;
    _rect.y = y;
}

void Button::setSize(int w, int h)
{
    _rect.w = w;
    _rect.h = h;
}

void Button::Draw()
{
    //* Draw Rect
    SDL_BlendMode oldBlendMode;
    SDL_GetRenderDrawBlendMode(_renderer, &oldBlendMode);

    // Activer le blending pour le bouton
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(_renderer, _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(_renderer, &_rect);

    // Restaurer le blend mode d'origine
    SDL_SetRenderDrawBlendMode(_renderer, oldBlendMode);


    //* Draw Text
    SDL_Surface* textSurface = TTF_RenderText_Solid(_font, _label.c_str(), _text_color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);

    int textW, textH;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textW,&textH);
    SDL_Rect textRect = {
        _rect.x + (_rect.w - textW) / 2,
        _rect.y + (_rect.h - textH) / 2,
        textW, textH
    };

    SDL_RenderCopy(_renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void Button::handleInput(SDL_Event& event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        int x = event.button.x;
        int y = event.button.y;
        if(this->isCLicked(x,y))
        {
            std::cout << "Button : [" << _label << "] is clicked" << std::endl;
        }

    }
}

bool Button::isCLicked(int mouseX, int mouseY)const
{
    return (mouseX >= _rect.x && mouseX <= _rect.x + _rect.w &&
                mouseY >= _rect.y && mouseY <= _rect.y + _rect.h);
}