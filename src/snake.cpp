#include "snake.h"

Snake::Snake(SDL_Renderer *renderer)
{
    this->renderer = renderer;
    this->snake_head = {500, 500, 10, 10};
    this->current_direction = 0;
    this->last_direction = 0;
    this->snake_size = 1;
}

void Snake::move()
{
    // Refuser les demi-tours
    bool invalid =
        (last_direction == UP && current_direction == DOWN) ||
        (last_direction == DOWN && current_direction == UP) ||
        (last_direction == LEFT && current_direction == RIGHT) ||
        (last_direction == RIGHT && current_direction == LEFT);

    // Si input invalide, on garde la dernière direction
    int dir = invalid ? last_direction : current_direction;

    // Appliquer le déplacement
    switch (dir)
    {
    case DOWN:
        snake_head.y += 10;
        break;
    case UP:
        snake_head.y -= 10;
        break;
    case LEFT:
        snake_head.x -= 10;
        break;
    case RIGHT:
        snake_head.x += 10;
        break;
    }

    // Met à jour la dernière direction **seulement si le mouvement est valide**
    if (!invalid)
        last_direction = dir;
}

void Snake::handleInput(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_DOWN)
        {
            current_direction = DOWN;
        }
        if (event.key.keysym.sym == SDLK_UP)
        {
            current_direction = UP;
        }
        if (event.key.keysym.sym == SDLK_LEFT)
        {
            current_direction = LEFT;
        }
        if (event.key.keysym.sym == SDLK_RIGHT)
        {
            current_direction = RIGHT;
        }
    }
}

void Snake::handleCollisions(std::vector<Apple> &apples)
{
    handleEnvironnementCollision();
    handleApplesCollisions(apples);
    handleSelfCollisions();
}

void Snake::handleSelfCollisions()
{
    std::for_each(snake_body.begin(), snake_body.end(), [&](auto &snake_segment)
                  {
        if(snake_head.x == snake_segment.x && snake_head.y == snake_segment.y && snake_size > 1)
        {
            snake_size = 1;
            handleLoose();

        } });
}

void Snake::handleApplesCollisions(std::vector<Apple> &apples)
{
    std::for_each(apples.begin(), apples.end(), [&](Apple &apple)
                  {
            if(snake_head.x == apple._rect.x && snake_head.y == apple._rect.y)
            {
                snake_size += 10;
                apple._rect.x = -10;
                apple._rect.y = -10;

                SDL_Color c = apple._color;

                if (c.r == 255 && c.g == 0 && c.b == 0 && c.a == 255) {
                    // Rouge (50%)
                    // Faire quelque chose
                    addPointCallback(1);

                } else if (c.r == 0 && c.g == 255 && c.b == 0 && c.a == 255) {
                    // Vert (30%)
                    // Faire autre chose
                    addPointCallback(3);

                } else if (c.r == 255 && c.g == 255 && c.b == 0 && c.a == 255) {
                    // Jaune (20%)
                    // Encore autre chose
                    addPointCallback(10);
                }

                generateApplesCallback();

            } });
}

void Snake::handleEnvironnementCollision()
{
    if (snake_head.x < 5 || snake_head.y < 5 || snake_head.x >= 980 || snake_head.y >= 980)
    {
        handleLoose();
    }
}

void Snake::setCallback(std::function<void()> lose, std::function<void(int)> addPoint, std::function<void()> generateApples)
{
    this->loseCallback = lose;
    this->addPointCallback = addPoint;
    this->generateApplesCallback = generateApples;
}

void Snake::handleLoose()
{
    loseCallback();
    generateApplesCallback();
    current_direction = 0;
    snake_size = 1;
    snake_head.x = 500;
    snake_head.y = 500;
}

void Snake::updateSnake()
{
    snake_body.push_front(snake_head);
    while (snake_body.size() > snake_size)
        snake_body.pop_back();
}

void Snake::Draw()
{
    SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, 255);
    std::for_each(snake_body.begin(), snake_body.end(), [&](auto &snake_segment)
                  { SDL_RenderFillRect(renderer, &snake_segment); });
}

Snake::~Snake()
{
    delete this;
}