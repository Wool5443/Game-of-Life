#include <iostream>
#include <SDL2/SDL.h>
#include "WindowProperties.hpp"
#include "GameOfLife.hpp"
#include "GameDrawer.hpp"
#include "EventHandler.hpp"
#include "FieldModifier.hpp"

constexpr int FIELD_WIDTH  = 192;
constexpr int FIELD_HEIGHT = 108;

constexpr uint64_t CLOCK_FREQUENCY = 2400000000; // 2.4 GHz

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
    bool         windowRunning         = true;
    bool         gameRunning           = false;
    bool         runOnlyNextGeneration = false;
    DrawingState state                 = DRAWING_STATE_IDLE;
    int          delay                 = DEFAULT_DELAY;

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (!surface)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return ERROR_SDL;
    }

    ErrorCode error = EVERYTHING_FINE;

    Game game(FIELD_WIDTH, FIELD_WIDTH, error);
    RETURN_ERROR(error);

    InitDrawing(surface->format);

    Timer gameTimer = {};

    while (windowRunning)
    {
        while (SDL_PollEvent(&e))
        {
            gameTimer.Start();

            switch (e.type)
            {
                case SDL_QUIT:
                    windowRunning = false;
                    break;
                case SDL_KEYDOWN:
                    KeyboardHandler(e, windowRunning, gameRunning,
                                    runOnlyNextGeneration, delay);
                    break;
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEBUTTONDOWN:
                    MouseButtonHandler(e, game, state);
                    break;
                case SDL_MOUSEWHEEL:
                    MouseWheelHandler(e, delay);
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

        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        FieldModify(game, state, x, y);

        GameDraw(surface, game);
        SDL_UpdateWindowSurface(window);
        
        if (gameRunning)
        {
            if (runOnlyNextGeneration)
            {
                gameRunning = false;
                runOnlyNextGeneration = false;
            }
            RETURN_ERROR(game.RunNewGeneration());

            uint64_t deltaTimeMs = gameTimer.Stop() * 1000 / CLOCK_FREQUENCY;
            int      realDelay   = deltaTimeMs < delay ? delay - deltaTimeMs : 0; // to keep constant delay

            SDL_Delay(realDelay);
            gameTimer.Start();
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
