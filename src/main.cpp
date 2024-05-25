#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "WindowProperties.hpp"
#include "GameOfLife.hpp"
#include "GameDrawer.hpp"
#include "EventHandler.hpp"
#include "FieldModifier.hpp"
#include "GraphUtils.hpp"

constexpr int FIELD_WIDTH  = 192;
constexpr int FIELD_HEIGHT = 108;

constexpr int MS_IN_SEC    = 1000;

constexpr const char* DIGITS_PATH = "../resources/numbers2.png";

constexpr uint64_t CLOCK_FREQUENCY = 2400000000; // 2.4 GHz

int main()
{
    errno = EVERYTHING_FINE;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) fprintf(stderr, "%s\n", SDL_GetError());
    if (IMG_Init(IMG_INIT_PNG) != 0) fprintf(stderr, "%s\n", SDL_GetError());

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
    int          goalFrameTime                 = DEFAULT_DELAY;

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (!surface)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return ERROR_SDL;
    }
    SDL_Surface* digits  = IMG_Load(DIGITS_PATH);
    if (!digits)
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
                                    runOnlyNextGeneration, goalFrameTime);
                    break;
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEBUTTONDOWN:
                    MouseButtonHandler(e, game, state);
                    break;
                case SDL_MOUSEWHEEL:
                    MouseWheelHandler(e, goalFrameTime);
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

        gameTimer.Start();

        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);
        FieldModify(game, state, x, y);

        GameDraw(surface, game);
        SDL_UpdateWindowSurface(window);
        
        if (gameRunning)
        {
            RETURN_ERROR(game.RunNewGeneration());

            if (runOnlyNextGeneration)
            {
                gameRunning = false;
                runOnlyNextGeneration = false;
            }
            else
            {
                uint64_t frameTime = gameTimer.Stop() * MS_IN_SEC / CLOCK_FREQUENCY;
                int      fps       = MS_IN_SEC / frameTime;
                ShowFps(surface, digits, fps);

                // keeping constant frame time
                int      toWait    = frameTime < goalFrameTime ? goalFrameTime - frameTime : 0;

                SDL_Delay(toWait);
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
