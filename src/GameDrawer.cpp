#include "GameDrawer.hpp"

static uint32_t LIVE_CELL_COLOR  = 0;
static uint32_t BACKGROUND_COLOR = 0;
static uint32_t GRID_COLOR       = 0;

static void _drawCell(SDL_Surface* surface, char value, int row, int col);

void InitDrawing(SDL_PixelFormat* format)
{
    BACKGROUND_COLOR = SDL_MapRGBA(format, 0x00, 0x00, 0x00, 0xff);
    LIVE_CELL_COLOR  = SDL_MapRGBA(format, 0xff, 0x00, 0x00, 0xff);
    GRID_COLOR       = SDL_MapRGBA(format, 0x60, 0x60, 0x60, 0xff);
}

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

void DrawGrid(SDL_Surface* surface)
{
    MyAssertHard(surface, ERROR_NULLPTR);

    int linesCountV = surface->w / CELL_SIZE + 1;
    int linesCountH = surface->h / CELL_SIZE + 1;

    SDL_Rect* lines = new SDL_Rect[linesCountV + linesCountH];
    if (!lines)
    {
        PRINT_ERROR(ERROR_NO_MEMORY);
        return;
    }

    for (int x = -1, i = 0; i < linesCountV; i++, x += CELL_SIZE)
        lines[i] = { .x = x, .y = 0, .w = GRID_LINE_WIDTH, .h = surface->h };
    

    for (int y = -1, i = linesCountV; i < linesCountV + linesCountH; i++, y += CELL_SIZE)
        lines[i] = { .x = 0, .y = y, .w = surface->w, .h = GRID_LINE_WIDTH };

    SDL_LockSurface(surface);
    SDL_FillRect(surface, nullptr, BACKGROUND_COLOR);
    SDL_FillRects(surface, lines, linesCountV + linesCountH, GRID_COLOR);
    SDL_UnlockSurface(surface);

    delete[] lines;
}

static SDL_Rect _cellRect = { .x = 0, .y = 0, .w = CELL_SIZE - 1, .h = CELL_SIZE - 1 };
void _drawCell(SDL_Surface* surface, char value, int row, int col)
{
    MyAssertHard(surface, ERROR_NULLPTR);

    GET_SCREEN_COORDINATES(row, col);

    _cellRect.x = x;
    _cellRect.y = y;

    uint32_t color = value == ALIVE ? LIVE_CELL_COLOR : BACKGROUND_COLOR;

    SDL_LockSurface(surface);
    SDL_FillRect(surface, &_cellRect, color);
    SDL_UnlockSurface(surface);
}
