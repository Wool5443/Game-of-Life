#include <errno.h>
#include "GameField.hpp"

char* _fieldCreator(int size);

GameField::GameField(int width, int height)
{
    this->width  = width;
    this->height = height;
    this->size   = width * height;
    
    this->field = _fieldCreator(this->size);

    if (!this->field)
        errno = ERROR_NO_MEMORY;
}

ErrorCode GameField::Verify()
{
    if (!this->field) return ERROR_NO_MEMORY;
    if (this->height < 0 || this->width < 0) return ERROR_BAD_FIELDS;

    return EVERYTHING_FINE;
}

ErrorCode GameField::Dump(const char* filePath)
{
    MyAssertSoft(filePath, ERROR_NULLPTR);

    RETURN_ERROR(this->Verify());

    FILE* file = fopen(filePath, "w");
    if (!file) return ERROR_BAD_FILE;

    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            fprintf(file, "%2hhx ", this->GetCellRef(i, j));
        }
        putc('\n', file);
    }
    fclose(file);

    return EVERYTHING_FINE;
}

char GameField::GetCellValue(int i, int j)
{
    if (0 <= i && i < this->height &&
        0 <= j && j < this->width)
        return this->GetCellRef(i, j);
    return DEAD;
}

void GameField::SetCellValue(int i, int j, char value)
{
    if (0 <= i && i < this->height &&
        0 <= j && j < this->width)
        this->GetCellRef(i, j) = value;
}

char* _fieldCreator(int size)
{
    return (char*)calloc(size, 1);
}
