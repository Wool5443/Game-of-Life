#include "EventHandler.hpp"
#include "Utils.hpp"

void KeyboardHandler(SDL_Event* e, bool* running)
{
    MyAssertHard(e, ERROR_NULLPTR);
    MyAssertHard(running, ERROR_NULLPTR);

    switch (e->key.keysym.sym)
    {
        case SDLK_x:
            *running = false;
            break;
        default:
            break;
    }
}

void MouseButtonHandler(SDL_Event* e)
{

}

void MouseWheelHandler(SDL_Event* e)
{

}
