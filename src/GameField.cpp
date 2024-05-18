#include <errno.h>
#include "GameField.hpp"

char* _fieldCreator(int size);

GameField::GameField(int width, int height)
    :   width{width},
        height{height},
        size{width * height},
        field{_fieldCreator(size)}
{
    if (!this->field)
        errno = ERROR_NO_MEMORY;
}

GameField::~GameField()
{
    this->width  = 0;
    this->height = 0;
    this->size   = 0;
    free(this->field);
    this->field  = nullptr;
}

ErrorCode GameField::Verify()
{
    if (!this->field) return ERROR_NO_MEMORY;
    if (this->height < 0 || this->width < 0) return ERROR_BAD_FIELDS;

    return EVERYTHING_FINE;
}

ErrorCode GameField::Dump(FILE* stream)
{
    MyAssertSoft(stream, ERROR_BAD_FILE);

    RETURN_ERROR(this->Verify());

    fprintf(stream, "---------------------------\n");

    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            fprintf(stream, "%2hhx ", this->GetCellRef(i, j));
        }
        putc('\n', stream);
    }

    fprintf(stream, "---------------------------\n");

    return EVERYTHING_FINE;
}

ErrorCode GameField::Dump(const char* filePath)
{
    MyAssertSoft(filePath, ERROR_NULLPTR);

    FILE* file = fopen(filePath, "w");
    if (!file) return ERROR_BAD_FILE;

    RETURN_ERROR(this->Dump(file));

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
