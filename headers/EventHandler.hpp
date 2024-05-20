#pragma once

#include <SDL2/SDL.h>

void KeyboardHandler(SDL_Event* e, bool* running);

void MouseButtonHandler(SDL_Event* e);

void MouseWheelHandler(SDL_Event* e);
