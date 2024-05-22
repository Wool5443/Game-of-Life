#include "EventHandler.hpp"
#include "Utils.hpp"
#include "GameDrawer.hpp"

inline int __attribute__((always_inline)) _newDelay(int delay, int modifier)
{
    int newDelay = delay + modifier;

    if (newDelay > MAX_DELAY)
        newDelay = MAX_DELAY;
    else if (newDelay < 0)
        newDelay = 0;

    return newDelay;
}

void KeyboardHandler(SDL_Event& e, bool& windowRunning , bool& gameRunning, int& delay)
{
    switch (e.key.keysym.sym)
    {
        case SDLK_x:
            windowRunning = false;
            break;
        case SDLK_p:
            gameRunning   = !gameRunning;
            break;
        case SDLK_EQUALS:
            delay = _newDelay(delay, DELAY_CHANGER);
            break;
        case SDLK_MINUS:
            delay = _newDelay(delay, DELAY_CHANGER);
            break;
        case SDLK_c:
            delay = DEFAULT_DELAY;
            break;
        default:
            break;
    }
}

void MouseButtonHandler(SDL_Event& e, Game& game, DrawingState& state)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.button.button == SDL_BUTTON_LEFT)
            state = DRAWING_STATE_DRAWING;
        else if (e.button.button == SDL_BUTTON_RIGHT)
            state = DRAWING_STATE_IDLE;
    }
    else
    {
        state = DRAWING_STATE_IDLE;
    }
}

void MouseWheelHandler(SDL_Event& e, int& delay)
{
    if (e.wheel.y > 0)
        delay = _newDelay(delay, DELAY_CHANGER);
    else
        delay = _newDelay(delay, -DELAY_CHANGER);
}
