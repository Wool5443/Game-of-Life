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
    else
        errno = EVERYTHING_FINE;
}

GameField::~GameField()
{
    this->width  = 0;
    this->height = 0;
    this->size   = 0;
    free(this->field);
    this->field  = nullptr;
}

ErrorCode GameField::Verify() const
{
    if (!this->field) return ERROR_NO_MEMORY;
    if (this->height < 0 || this->width < 0) return ERROR_BAD_FIELDS;

    return EVERYTHING_FINE;
}

ErrorCode GameField::Dump(FILE* stream) const
{
    MyAssertSoft(stream, ERROR_BAD_FILE);

    RETURN_ERROR(this->Verify());

    fprintf(stream, "---------------------------\n");

    for (int row = 0; row < this->height; row++)
    {
        for (int col = 0; col < this->width; col++)
        {
            fprintf(stream, "%2hhx ", this->GetCellRef(row, col));
        }
        putc('\n', stream);
    }

    fprintf(stream, "---------------------------\n");

    return EVERYTHING_FINE;
}

ErrorCode GameField::Dump(const char* filePath) const
{
    MyAssertSoft(filePath, ERROR_NULLPTR);

    FILE* file = fopen(filePath, "w");
    if (!file) return ERROR_BAD_FILE;

    RETURN_ERROR(this->Dump(file));

    fclose(file);

    return EVERYTHING_FINE;
}

char GameField::GetCellValue(int row, int col) const
{
    if (0 <= row && row < this->height &&
        0 <= col && col < this->width)
        return this->GetCellRef(row, col);
    return DEAD;
}

void GameField::SetCellValue(int row, int col, char value)
{
    if (0 <= row && row < this->height &&
        0 <= col && col < this->width)
        this->GetCellRef(row, col) = value;
}

char* _fieldCreator(int size)
{
    return (char*)calloc(size, 1);
}
