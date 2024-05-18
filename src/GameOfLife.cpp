#include "GameOfLife.hpp"

ErrorCode Game::Init()
{
    return this->Init(DEFUALT_WIDTH, DEFUALT_HEIGHT);
}

ErrorCode Game::Init(size_t fieldWidth, size_t fieldHeight)
{
    this->fieldWidth  = fieldWidth;
    this->fieldHeight = fieldHeight;

    char* field = new char[fieldWidth * fieldHeight];
    if (!field) return ERROR_NO_MEMORY;

    this->field = field;

    return EVERYTHING_FINE;
}

ErrorCode Game::Destructor()
{
    RETURN_ERROR(this->Verify());

    this->fieldWidth  = SIZET_POISON;
    this->fieldHeight = SIZET_POISON;
    free(this->field);
    this->field       = nullptr;

    return EVERYTHING_FINE;
}

ErrorCode Game::Verify()
{
    if (!this->field) return ERROR_NO_MEMORY;
    if (!this->fieldWidth || !this->fieldHeight) return ERROR_BAD_FIELDS;

    return EVERYTHING_FINE;
}
