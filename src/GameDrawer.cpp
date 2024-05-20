#include "GameDrawer.hpp"

void _drawCell(SDL_Surface* surface, char value, int row, int col);

void GameDraw(SDL_Surface* surface, const Game& game)
{
    MyAssertHard(surface, ERROR_NULLPTR);

    for (int row = 0; row < game.GetField().width; row++)
    {
        for (int col = 0; col < game.GetField().height; col++)
        {
            _drawCell(surface, game.GetField().GetCellValue(row, col), row, col);
        }
    }
}

static SDL_Rect _cellRect = { .x = 0, .y = 0, .w = CELL_SIZE - 1, .h = CELL_SIZE - 1 };
void _drawCell(SDL_Surface* surface, char value, int row, int col)
{
    MyAssertHard(surface, ERROR_NULLPTR);

    int x = col * CELL_SIZE;
    int y = row * CELL_SIZE;

    _cellRect.x = x;
    _cellRect.y = y;

    uint32_t color = value == ALIVE ? LIVE_CELL_COLOR : DEAD_CELL_COLOR;

    SDL_LockSurface(surface);
    SDL_FillRect(surface, &_cellRect, color);
    SDL_UnlockSurface(surface);
}
