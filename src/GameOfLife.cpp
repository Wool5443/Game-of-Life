#include <errno.h>
#include "GameOfLife.hpp"

Game::Game(int fieldWidth, int fieldHeight)
    :   oldField{new GameField(fieldWidth, fieldHeight)},
        newField{new GameField(fieldWidth, fieldHeight)}
    {
        if (!oldField || !newField)
            errno = ERROR_NO_MEMORY;
    }

Game::~Game()
{
    delete oldField;
    delete newField;

    oldField = nullptr;
    newField = nullptr;
}

ErrorCode Game::Verify() const
{
    return EVERYTHING_FINE;
}

ErrorCode Game::Dump(FILE* stream) const
{
    MyAssertSoft(stream, ERROR_BAD_FILE);
    RETURN_ERROR(oldField->Dump(stream));

    return EVERYTHING_FINE;
}

ErrorCode Game::Dump(const char* filePath) const
{
    MyAssertSoft(filePath, ERROR_NULLPTR);
    RETURN_ERROR(oldField->Dump(filePath));

    return EVERYTHING_FINE;
}

ErrorCode Game::RunNewGeneration()
{
    int neighbors = 0;

    for (int i = 0; i < this->oldField->height; i++)
    {
        for (int j = 0; j < this->oldField->width; j++)
        {
            neighbors = 
                oldField->GetCellValue(i - 1, j - 1) +
                oldField->GetCellValue(i - 1, j) +
                oldField->GetCellValue(i - 1, j + 1) +

                oldField->GetCellValue(i, j - 1) +
                oldField->GetCellValue(i, j + 1) +

                oldField->GetCellValue(i + 1, j - 1) +
                oldField->GetCellValue(i + 1, j) +
                oldField->GetCellValue(i + 1, j + 1);

            char& oldCell = oldField->GetCellRef(i, j);
            char& newCell = newField->GetCellRef(i, j);

            if (oldCell == ALIVE)
            {
                if (neighbors < 2 || neighbors > 3)
                    newCell = DEAD;
                else
                    newCell = ALIVE;
            }
            else if (neighbors == 3)
                newCell = ALIVE;
            else
                newCell = DEAD;
        }
    }

    GameField* swapper = this->oldField;
    this->oldField     = this->newField;
    this->newField     = swapper;

    return EVERYTHING_FINE;
}
