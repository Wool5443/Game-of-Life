#include "GameDrawer.hpp"

constexpr int CELL_SIZE = 10;

ErrorCode _drawCell(SDL_Surface* surface, char value, int i, int j);

ErrorCode GameDraw(SDL_Surface* surface, const Game& game)
{
    MyAssertSoft(surface, ERROR_NULLPTR);

    for (int i = 0; i < game.GetField().width; i++)
    {
        for (int j = 0; j < game.GetField().height; j++)
        {
            _drawCell(surface, game.GetField().GetCellValue(i, j), i, j);
        }
    }

    return EVERYTHING_FINE;
}

static SDL_Rect _cellRect = { .x = 0, .y = 0, .w = CELL_SIZE, .h = CELL_SIZE };
ErrorCode _drawCell(SDL_Surface* surface, char value, int i, int j)
{
    MyAssertSoft(surface, ERROR_NULLPTR);

    int x = j * CELL_SIZE;
    int y = i * CELL_SIZE;

    _cellRect.x = x;
    _cellRect.y = y;

    uint32_t color = value == ALIVE ? LIVE_CELL_COLOR : DEAD_CELL_COLOR;

    if (value == ALIVE)
    {
        printf("ALIVE: x = %d, y = %d\n", x, y);
    }

    SDL_LockSurface(surface);
    SDL_FillRect(surface, &_cellRect, color);
    SDL_UnlockSurface(surface);

    return EVERYTHING_FINE;
}
