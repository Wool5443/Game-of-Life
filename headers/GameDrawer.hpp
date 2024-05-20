#pragma once

#include <SDL2/SDL.h>
#include "GameOfLife.hpp"
#include "Utils.hpp"

constexpr int CELL_SIZE = 10;

constexpr char ALPHA = 24;
constexpr char BLUE  =  0;
constexpr char GREEN =  8;
constexpr char RED   = 16;

constexpr uint32_t LIVE_CELL_COLOR = (0xff << RED) + (0xff << ALPHA);
constexpr uint32_t DEAD_CELL_COLOR = (0xff << ALPHA);

void GameDraw(SDL_Surface* surface, const Game& game);
