#include <stdexcept>
#include "board.hpp"

int Board::compareRow(std::string position, std::string targetRow)
{
    if (position.length() < 2 || targetRow.length() < 1)
    {
        throw std::invalid_argument("Invalid position or target row format");
    }

    int posRow = position[1] - '0';
    int target = targetRow[0] - '0';

    if (posRow <= 0 || posRow > 8)
    {
        throw std::invalid_argument("Invalid position row");
    }
    if (target <= 0 || target > 8)
    {
        throw std::invalid_argument("Invalid target row");
    }
    return posRow - target;
}
int Board::compareRow(std::string position, int targetRow)
{
    return 0;
}
std::vector<std::string> Board::generateMoves()
{
    return {};
}
/**
 * === REQUIREMENTS ===
 * Move Handling Requirements
 * move(move: string)
 * 1. A move must be supported by a string containing the start position of a piece,
 *    and the end position of a piece (for example "g1 g3" will move the white knight
 *    from it's intital position)
 * 2. A call to the move function must throw an error if the move is invalid
 * 3. The board state must be updated for the instance of the board object after the
 *    valid move function
 * Move generation requirements
 * generateMoves(pieceAtPosition?: string)
 * 1. Calling the function with no input will return a list of ALL valid moves.
 * 2. Calling the function with a string input for a piece position will return a
 *    list of valid moves for that piece
 * === Notes ===
 * Need a function to suggest moves. This could double as the function
 * used to play against a computer
 */