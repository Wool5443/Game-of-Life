#pragma once

#include "Utils.hpp"

constexpr char   ALIVE = 1;
constexpr char   DEAD  = 0;

struct GameField
{
    int   width;
    int   height;
    int   size;
    char* field;

    GameField(int width, int height);
    ~GameField();

    ErrorCode Verify() const;
    ErrorCode Dump(FILE* stream) const;
    ErrorCode Dump(const char* filePath) const;

    char& __attribute__((always_inline)) GetCellRef(int i, int j) const
    {
        return *(this->field + i * this->width + j);
    }

    char GetCellValue(int i, int j) const;
    void SetCellValue(int i, int j, char value);
};
