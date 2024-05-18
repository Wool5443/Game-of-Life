#pragma once

#include "Utils.hpp"

constexpr size_t DEFUALT_WIDTH  = 100;
constexpr size_t DEFUALT_HEIGHT = 100;

class Game
{
private:
    size_t fieldWidth;
    size_t fieldHeight;
    char*  field;

public:
    ErrorCode Init();
    ErrorCode Init(size_t fieldWidth, size_t fieldHeight);

    ErrorCode Verify();

    ErrorCode Destructor();
};
