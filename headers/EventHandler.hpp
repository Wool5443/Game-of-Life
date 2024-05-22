#pragma once

#include <SDL2/SDL.h>
#include "GameOfLife.hpp"
#include "FieldModifier.hpp"

constexpr int DELAY_CHANGER = 5;
constexpr int DEFAULT_DELAY = 50;
constexpr int MAX_DELAY     = 200;

void KeyboardHandler(SDL_Event& e, bool& running, bool& paused, int& delay);

void MouseButtonHandler(SDL_Event& e, Game& game, DrawingState& state);

void MouseWheelHandler(SDL_Event& e, int& delay);
