#pragma once

#include <SDL2/SDL.h>
#include "GameOfLife.hpp"

enum DrawingState
{
    DRAWING_STATE_IDLE,
    DRAWING_STATE_DRAWING,
    DRAWING_STATE_ERASING,
};

void FieldModify(Game& game, DrawingState state, int x, int y);
