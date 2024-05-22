#pragma once

#include "GameField.hpp"

class Game
{
    GameField* oldField;
    GameField* newField;

    ErrorCode dump(FILE* stream);

public:
    Game(int fieldWidth, int fieldHeight, ErrorCode& error);
    ~Game();

    GameField& __attribute__((always_inline)) GetField() const
    {
        return *oldField;
    }

    ErrorCode Verify() const ;

    ErrorCode Dump(FILE* stream) const;
    ErrorCode Dump(const char* filePath) const;

    ErrorCode RunNewGeneration();
};
