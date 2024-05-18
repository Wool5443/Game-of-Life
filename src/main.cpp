#include "GameOfLife.hpp"

int main()
{
    Game game(10, 10);

    PRINT_ERROR(game.Run());

    return 0;
}
