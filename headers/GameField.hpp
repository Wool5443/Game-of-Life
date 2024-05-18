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

    GameField() : width{0}, height{0}, size{0}, field{nullptr} {}
    GameField(int width, int height);
    ~GameField();

    ErrorCode Verify();
    ErrorCode Dump(const char* filePath);

    char& __attribute__((always_inline)) GetCellRef(int i, int j)
    {
        return *(this->field + i * this->width + j);
    }

    char GetCellValue(int i, int j);
    void SetCellValue(int i, int j, char value);
};
