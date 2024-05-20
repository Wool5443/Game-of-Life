#include "WindowProperties.hpp"
#include "GameDrawer.hpp"

constexpr int CELL_SIZE = 10;
constexpr int CELLS_IN_ROW = WINDOW_WIDTH / CELL_SIZE;
constexpr int CELLS_IN_COL = WINDOW_HEIGHT / CELL_SIZE;

ErrorCode _drawCell(SDL_Surface* surface, char value, int i, int j);

ErrorCode GameDraw(SDL_Surface* surface, const GameField& field)
{
    MyAssertSoft(surface, ERROR_NULLPTR);

    for (int i = 0; i < field.height; i++)
    {
        for (int j = 0; j < field.width; j++)
        {

        }
    }

    return EVERYTHING_FINE;
}

static SDL_Rect _cellRect = {};
ErrorCode _drawCell(SDL_Surface* surface, char value, int i, int j)
{
    MyAssertSoft(surface, ERROR_NULLPTR);

    int x = j * CELL_SIZE;
    int y = i * CELLS_IN_ROW * CELL_SIZE;

    _cellRect.x = x;
    _cellRect.y = y;
    _cellRect.w = CELL_SIZE;
    _cellRect.h = CELL_SIZE;

    if (value == ALIVE)
    {
        SDL_FillRect(surface, &_cellRect, LIVE_CELL_COLOR);
    }

    return EVERYTHING_FINE;
}
