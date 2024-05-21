#include "EventHandler.hpp"
#include "Utils.hpp"
#include "GameDrawer.hpp"

void KeyboardHandler(SDL_Event* e, bool* windowRunning , bool* gameRunning )
{
    MyAssertHard(e, ERROR_NULLPTR);
    MyAssertHard(windowRunning, ERROR_NULLPTR);
    MyAssertHard(gameRunning,   ERROR_NULLPTR);

    switch (e->key.keysym.sym)
    {
        case SDLK_x:
            *windowRunning = false;
            break;
        case SDLK_p:
            *gameRunning   = !*gameRunning;
            break;
        default:
            break;
    }
}

void MouseButtonHandler(SDL_Event* e, Game& game)
{
    MyAssertHard(e, ERROR_NULLPTR);

    int x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    x -= 3;
    y -= 3;

    int row = y / CELL_SIZE;
    int col = x / CELL_SIZE;

    if (e->button.button == SDL_BUTTON_LEFT)
        game.GetField().SetCellValue(row, col, ALIVE);
    else if (e->button.button == SDL_BUTTON_RIGHT)
        game.GetField().SetCellValue(row, col, DEAD);
}

void MouseWheelHandler(SDL_Event* e)
{
    MyAssertHard(e, ERROR_NULLPTR);
}
