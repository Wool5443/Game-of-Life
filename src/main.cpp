#include <errno.h>
#include <SDL2/SDL.h>
#include "WindowProperties.hpp"
#include "GameOfLife.hpp"
#include "GameDrawer.hpp"
#include "EventHandler.hpp"

constexpr int FIELD_WIDTH  = 1000;
constexpr int FIELD_HEIGHT = 1000;

int main()
{
    errno = EVERYTHING_FINE;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) fprintf(stderr, "%s\n", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, -1, -1, WINDOW_WIDTH, WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return ERROR_SDL;
    }

    SDL_Event e  = {};
    bool windowRunning = true;
    bool gameRunning   = false;

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (!surface)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return ERROR_SDL;
    }

    Game game(FIELD_WIDTH, FIELD_WIDTH);
    RETURN_ERROR((ErrorCode)errno);

    InitDrawing(surface->format);

    while (windowRunning)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    windowRunning = false;
                    break;
                case SDL_KEYDOWN:
                    KeyboardHandler(&e, &windowRunning, &gameRunning);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    MouseButtonHandler(&e, game);
                    break;
                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                        surface = SDL_GetWindowSurface(window);
                    DrawGrid(surface);
                    break;
                default:
                    break;
            }
        }

        GameDraw(surface, game);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(50);
        if (gameRunning)
            RETURN_ERROR(game.RunNewGeneration());
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
