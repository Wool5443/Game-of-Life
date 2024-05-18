#include <errno.h>
#include "GameOfLife.hpp"

char* _oldFieldCreator(int size);

Game::Game(int fieldWidth, int fieldHeight)
{
    this->oldField = GameField(fieldWidth, fieldHeight);
    this->oldField = GameField(fieldWidth, fieldHeight);

    errno = EVERYTHING_FINE;
}

ErrorCode Game::Verify()
{
    return EVERYTHING_FINE;
}

ErrorCode Game::Dump(const char* filePath)
{
    MyAssertSoft(filePath, ERROR_NULLPTR);
    RETURN_ERROR(this->oldField.Dump(filePath));

    return EVERYTHING_FINE;
}

ErrorCode Game::Run()
{
    while (true)
    {

    }

    return EVERYTHING_FINE;
}

ErrorCode Game::runNewGeneration()
{
    int neighbors = 0;

    for (int i = 0; i < this->oldField.height; i++)
    {
        for (int j = 0; j < this->oldField.width; j++)
        {
            neighbors = 
                this->oldField.GetCellValue(i - 1, j - 1) +
                this->oldField.GetCellValue(i - 1, j) +
                this->oldField.GetCellValue(i - 1, j + 1) +

                this->oldField.GetCellValue(i, j - 1) +
                this->oldField.GetCellValue(i, j + 1) +

                this->oldField.GetCellValue(i + 1, j - 1) +
                this->oldField.GetCellValue(i + 1, j) +
                this->oldField.GetCellValue(i + 1, j + 1);

            char& newCellState = this->newField.GetCellRef(i, j);
            if (newCellState == ALIVE)
            {
                if (neighbors < 2 || neighbors > 3)
                    newCellState = DEAD;
            }
            else if (neighbors == 3)
                newCellState = ALIVE;

            GameField swapper = this->oldField;
            this->oldField = this->newField;
            this->newField = swapper;
        }
    }

    return EVERYTHING_FINE;
}
