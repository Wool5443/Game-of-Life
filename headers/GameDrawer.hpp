#pragma once

#include <SDL2/SDL.h>
#include "GameField.hpp"
#include "Utils.hpp"

constexpr uint32_t LIVE_CELL_COLOR = 0xffffffff;
constexpr uint32_t DEAD_CELL_COLOR = 0x000000ff;

ErrorCode GameDraw(SDL_Surface* surface, const GameField& field);
