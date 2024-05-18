#include "GameOfLife.hpp"

int main()
{
    Game game(100, 100);

    PRINT_ERROR(game.Run());

    return 0;
}
