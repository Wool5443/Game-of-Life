#pragma once

#include <SDL2/SDL.h>
#include "GameOfLife.hpp"
#include "Utils.hpp"

constexpr int CELL_SIZE       = 20;
constexpr int GRID_LINE_WIDTH = 1;

#define GET_FIELD_COORDINATES(x, y) int row = (y) / CELL_SIZE, col = (x) / CELL_SIZE
#define GET_SCREEN_COORDINATES(row, col) int x = (col) * CELL_SIZE, y = (row) * CELL_SIZE

void InitDrawing(SDL_PixelFormat* format);

void GameDraw(SDL_Surface* surface, const Game& game);

void DrawGrid(SDL_Surface* surface);
