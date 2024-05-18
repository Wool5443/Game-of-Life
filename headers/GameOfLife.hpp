#pragma once

#include "GameField.hpp"

class Game
{
    GameField* oldField;
    GameField* newField;

    ErrorCode dump(FILE* stream);

    ErrorCode runNewGeneration();

public:
    Game(int fieldWidth, int fieldHeight);
    ~Game();

    ErrorCode Verify();

    ErrorCode Dump(FILE* stream);
    ErrorCode Dump(const char* filePath);

    ErrorCode Run();
};
