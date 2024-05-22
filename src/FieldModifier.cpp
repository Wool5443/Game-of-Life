#include "FieldModifier.hpp"
#include "GameDrawer.hpp"

void FieldModify(Game& game, DrawingState state, int x, int y)
{
    if (state == DRAWING_STATE_IDLE)
        return;

    GameField& field = game.GetField();
    GET_FIELD_COORDINATES(x, y);

    fieldCell_t& cell = field.GetCellRef(row, col);

    switch (state)
    {
        case DRAWING_STATE_DRAWING:
            cell = ALIVE;
            break;
        case DRAWING_STATE_ERASING:
            cell = DEAD;
            break;
        default:
            PRINT_ERROR(ERROR_BAD_VALUE);
            break;
    }
}
