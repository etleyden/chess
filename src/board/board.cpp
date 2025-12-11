#include <stdexcept>
#include "board.hpp"

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
Board::Piece Board::getPieceAtPosition(std::string position)
{
    uint64_t bitmask = getBitmaskForPosition(position);
    for (int i = 0; i < 12; ++i)
    {
        if (pieces[i] & bitmask)
        {
            return static_cast<Piece>(i);
        }
    }
    return EMPTY;
}
uint64_t Board::getBitmaskForBoard()
{
    uint64_t bitmask = 0;
    for (int i = 0; i < 12; ++i)
    {
        bitmask |= pieces[i];
    }
    return bitmask;
}
bool Board::getTurn()
{
    return whiteTurn;
}
uint64_t Board::getMovesForPieceAtPosition(std::string position)
{
    // design requirements:
    // a) validate position input
    if (getBitmaskForPosition(position) == 0)
    {
        throw std::invalid_argument("Invalid position format");
    }
    // b) identify piece at position
    Piece piece = getPieceAtPosition(position);
    // c) if it is not their turn, throw an error
    if ((whiteTurn && piece >= BLACK_PAWN) || (!whiteTurn && piece <= WHITE_KING))
    {
        throw std::invalid_argument("It's not that player's turn");
    }
    // d) generate valid moves for that piece based on current board state and store it in a bitmask
    switch (piece)
    {
    case WHITE_PAWN:
    case BLACK_PAWN:
        return getMovesForPawnAtPosition(position);
        break;
    case WHITE_KNIGHT:
    case BLACK_KNIGHT:
        return getMovesForKnightAtPosition(position);
        break;
    case WHITE_BISHOP:
    case BLACK_BISHOP:
        return getMovesForBishopAtPosition(position);
        break;
    case WHITE_ROOK:
    case BLACK_ROOK:
        return getMovesForRookAtPosition(position);
        break;
    case WHITE_QUEEN:
    case BLACK_QUEEN:
        return getMovesForQueenAtPosition(position);
        break;
    case WHITE_KING:
    case BLACK_KING:
        return getMovesForKingAtPosition(position);
        break;
    default:
        throw std::invalid_argument("Unknown piece type");
    }
}