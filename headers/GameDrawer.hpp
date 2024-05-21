#pragma once

#include <SDL2/SDL.h>
#include "GameOfLife.hpp"
#include "Utils.hpp"

constexpr int CELL_SIZE       = 20;
constexpr int GRID_LINE_WIDTH = 1;

void InitDrawing(SDL_PixelFormat* format);

void GameDraw(SDL_Surface* surface, const Game& game);

void DrawGrid(SDL_Surface* surface);
