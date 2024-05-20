#include <errno.h>
#include <SDL2/SDL.h>
#include "WindowProperties.hpp"
#include "GameOfLife.hpp"
#include "GameDrawer.hpp"
#include "EventHandler.hpp"

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
    bool running = true;

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (!surface)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
        return ERROR_SDL;
    }

    Game game(10, 10);
    GameField field = game.GetField();
    field.SetCellValue(3, 3, 1);
    field.SetCellValue(3, 4, 1);
    field.SetCellValue(3, 5, 1);
    RETURN_ERROR((ErrorCode)errno);

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    KeyboardHandler(&e, &running);
                    break;
                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                        surface = SDL_GetWindowSurface(window);
                    break;
                default:
                    break;
            }
        }

        GameDraw(surface, game);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(100);
        RETURN_ERROR(game.RunNewGeneration());
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
