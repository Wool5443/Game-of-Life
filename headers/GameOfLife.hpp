#pragma once

#include "GameField.hpp"

class Game
{
    GameField oldField;
    GameField newField;

    ErrorCode runNewGeneration();

public:
    Game(int fieldWidth, int fieldHeight);

    ErrorCode Verify();

    ErrorCode Dump(const char* filePath);

    ErrorCode Run();
};
