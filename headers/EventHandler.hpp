#pragma once

#include <SDL2/SDL.h>
#include "GameOfLife.hpp"

void KeyboardHandler(SDL_Event* e, bool* running, bool* paused);

void MouseButtonHandler(SDL_Event* e, Game& game);

void MouseWheelHandler(SDL_Event* e);
