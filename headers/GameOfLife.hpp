#pragma once

#include "GameField.hpp"

class Game
{
    GameField* oldField;
    GameField* newField;

    ErrorCode dump(FILE* stream);

public:
    Game(int fieldWidth, int fieldHeight);
    ~Game();

    const char* __attribute__((always_inline)) GetField()
    {
        return (const char*)oldField->field;
    }

    ErrorCode Verify();

    ErrorCode Dump(FILE* stream);
    ErrorCode Dump(const char* filePath);

    ErrorCode RunNewGeneration();
};
