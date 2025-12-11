#include "board.hpp"
#include <stdexcept>
// === Basic Board Utilities ===
int Board::compareRow(std::string position, std::string targetRow)
{
    if (targetRow.length() < 1)
    {
        throw std::invalid_argument("Invalid position or target row format");
    }

    int target = targetRow[0] - '0';

    if (target <= 0 || target > 8)
    {
        throw std::invalid_argument("Invalid target row");
    }
    return compareRow(position, target);
}
int Board::compareRow(std::string position, int targetRow)
{
    if (position.length() < 2)
    {
        throw std::invalid_argument("Invalid position format");
    }
    int posRow = position[1] - '0';
    if (posRow <= 0 || posRow > 8)
    {
        throw std::invalid_argument("Invalid position row");
    }
    return posRow - targetRow;
}
int Board::compareColumn(std::string position, char targetColumn)
{
    if (position.length() < 1)
    {
        throw std::invalid_argument("Invalid position format");
    }

    char posColumn = position[0];

    if (posColumn < 'a' || posColumn > 'h')
    {
        throw std::invalid_argument("Invalid position column");
    }
    if (targetColumn < 'a' || targetColumn > 'h')
    {
        throw std::invalid_argument("Invalid target column");
    }

    return posColumn - targetColumn;
}
int Board::compareColumn(std::string position, int targetColumn)
{
    if (position.length() < 1)
    {
        throw std::invalid_argument("Invalid position format");
    }

    char posColumn = position[0];

    if (posColumn < 'a' || posColumn > 'h')
    {
        throw std::invalid_argument("Invalid position column");
    }
    if (targetColumn < 1 || targetColumn > 8)
    {
        throw std::invalid_argument("Invalid target column");
    }

    return (posColumn - 'a' + 1) - targetColumn;
}
// === Bitmask Utils ===
uint64_t Board::getBitmaskForPosition(std::string position)
{
    if (position.length() < 2)
    {
        throw std::invalid_argument("Invalid position format");
    }

    char file = position[0];
    char rank = position[1];

    if (file < 'a' || file > 'h' || rank < '1' || rank > '8')
    {
        throw std::invalid_argument("Position out of bounds");
    }

    int fileIndex = file - 'a';
    int rankIndex = rank - '1';

    return 1ULL << (rankIndex * 8 + fileIndex);
}
uint64_t Board::getBitmaskForRow(int row)
{
    if (row < 1 || row > 8)
    {
        throw std::invalid_argument("Row out of bounds");
    }

    return 0xFFULL << ((row - 1) * 8);
}
uint64_t Board::getBitmaskForColumn(char column)
{
    if (column < 'a' || column > 'h')
    {
        throw std::invalid_argument("Column out of bounds");
    }

    uint64_t bitmask = 0;
    int colIndex = column - 'a';

    return getBitmaskForColumn(colIndex + 1);
}
uint64_t Board::getBitmaskForColumn(int column)
{
    if (column < 1 || column > 8)
    {
        throw std::invalid_argument("Column out of bounds");
    }

    uint64_t bitmask = 0;
    int colIndex = column - 1;

    for (int row = 0; row < 8; ++row)
    {
        bitmask |= (1ULL << (row * 8 + colIndex));
    }

    return bitmask;
}
