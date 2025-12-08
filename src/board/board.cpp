#include <stdexcept>
#include "board.hpp"

Board::Board()
    : pieces{
          0x000000000000FF00, // WHITE_PAWN
          0x0000000000000042, // WHITE_KNIGHT
          0x0000000000000024, // WHITE_BISHOP
          0x0000000000000081, // WHITE_ROOK
          0x0000000000000008, // WHITE_QUEEN
          0x0000000000000010, // WHITE_KING
          0x00FF000000000000, // BLACK_PAWN
          0x4200000000000000, // BLACK_KNIGHT
          0x2400000000000000, // BLACK_BISHOP
          0x8100000000000000, // BLACK_ROOK
          0x0800000000000000, // BLACK_QUEEN
          0x1000000000000000  // BLACK_KING
      },
      whiteTurn(true),
      castlingRights(0b1111), // Both sides can castle both ways initially
      enPassantSquare(-1) // No en passant square initially
{
    // Constructor body can remain empty as initialization is done in the initializer list
}
Board::Board(std::string fen)
    : pieces{0}, whiteTurn(true), castlingRights(0), enPassantSquare(-1)
{
    int rank = 7;
    int file = 0;
    enum FEN_PART
    {
        PIECES,
        TURN,
        CASTLING,
        EN_PASSANT,
        HALF_MOVE,
        FULL_MOVE
    };
    FEN_PART currentPart = PIECES;
    for (char c : fen)
    {
        if (currentPart == PIECES)
        {
            if (pieceMap.find(c) != pieceMap.end())
            {
                int position = rank * 8 + file;
                Piece piece = pieceMap[c];
                pieces[piece] |= (1ULL << position);
                file++;
            }
            else if (c >= '1' && c <= '8')
            {
                file += (c - '0');
            }
            else if (c == '/')
            {
                rank--;
                file = 0;
            }
            else if (c == ' ')
            {
                currentPart = TURN;
            }
        }
        else if (currentPart == TURN)
        {
            if (c == 'w')
            {
                whiteTurn = true;
            }
            else if (c == 'b')
            {
                whiteTurn = false;
            }
            else if (c == ' ')
            {
                currentPart = CASTLING;
            }
            else
            {
                throw std::invalid_argument("Invalid FEN: Unknown turn character");
            }
        }
        else if (currentPart == CASTLING)
        {
            // TODO: Handle castling rights parsing here
            if (c == ' ')
            {
                currentPart = EN_PASSANT;
            }
        }
        else if (currentPart == EN_PASSANT)
        {
            // TODO: Handle en passant square parsing here
            if (c == ' ')
            {
                currentPart = HALF_MOVE;
            }
        }
        else if (currentPart == HALF_MOVE)
        {
            // TODO: Handle half-move clock parsing here
            if (c == ' ')
            {
                currentPart = FULL_MOVE;
            }
        }
        else
        {
            break;
        }
    }
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
// === Pieces and movement ===
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
uint64_t Board::getMovesForPawnAtPosition(std::string position)
{
    // Placeholder implementation
    return 0;
}
uint64_t Board::getMovesForKnightAtPosition(std::string position)
{
    // Placeholder implementation
    return 0;
}
uint64_t Board::getMovesForBishopAtPosition(std::string position)
{
    // Placeholder implementation
    return 0;
}
uint64_t Board::getMovesForRookAtPosition(std::string position)
{
    // Placeholder implementation
    return 0;
}
uint64_t Board::getMovesForQueenAtPosition(std::string position)
{
    // Placeholder implementation
    return 0;
}
uint64_t Board::getMovesForKingAtPosition(std::string position)
{
    // Placeholder implementation
    return 0;
}
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
// === Board Representation ===
std::string Board::boardToString() const
{
    std::string boardRepresentation;
    for (int row = 7; row >= 0; --row)
    {
        for (int col = 0; col < 8; ++col)
        {
            uint64_t square = 1ULL << (row * 8 + col);

            if (pieces[WHITE_PAWN] & square)
            {
                boardRepresentation += 'P';
            }
            else if (pieces[WHITE_KNIGHT] & square)
            {
                boardRepresentation += 'N';
            }
            else if (pieces[WHITE_BISHOP] & square)
            {
                boardRepresentation += 'B';
            }
            else if (pieces[WHITE_ROOK] & square)
            {
                boardRepresentation += 'R';
            }
            else if (pieces[WHITE_QUEEN] & square)
            {
                boardRepresentation += 'Q';
            }
            else if (pieces[WHITE_KING] & square)
            {
                boardRepresentation += 'K';
            }
            else if (pieces[BLACK_PAWN] & square)
            {
                boardRepresentation += 'p';
            }
            else if (pieces[BLACK_KNIGHT] & square)
            {
                boardRepresentation += 'n';
            }
            else if (pieces[BLACK_BISHOP] & square)
            {
                boardRepresentation += 'b';
            }
            else if (pieces[BLACK_ROOK] & square)
            {
                boardRepresentation += 'r';
            }
            else if (pieces[BLACK_QUEEN] & square)
            {
                boardRepresentation += 'q';
            }
            else if (pieces[BLACK_KING] & square)
            {
                boardRepresentation += 'k';
            }
            else
            {
                // Determine if the square is light or dark
                if ((row + col) % 2 == 1)
                {
                    boardRepresentation += 'X';
                }
                else
                {
                    boardRepresentation += ' ';
                }
            }
        }
        boardRepresentation += '\n'; // Newline after each row
    }
    return boardRepresentation;
}
std::string Board::generateFEN() const
{
    std::string fen;
    for (int rank = 7; rank >= 0; --rank)
    {
        int emptyCount = 0;
        for (int file = 0; file < 8; ++file)
        {
            uint64_t square = 1ULL << (rank * 8 + file);
            if (pieces[WHITE_PAWN] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'P';
            }
            else if (pieces[WHITE_KNIGHT] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'N';
            }
            else if (pieces[WHITE_BISHOP] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'B';
            }
            else if (pieces[WHITE_ROOK] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'R';
            }
            else if (pieces[WHITE_QUEEN] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'Q';
            }
            else if (pieces[WHITE_KING] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'K';
            }
            else if (pieces[BLACK_PAWN] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'p';
            }
            else if (pieces[BLACK_KNIGHT] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'n';
            }
            else if (pieces[BLACK_BISHOP] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'b';
            }
            else if (pieces[BLACK_ROOK] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'r';
            }
            else if (pieces[BLACK_QUEEN] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'q';
            }
            else if (pieces[BLACK_KING] & square)
            {
                if (emptyCount > 0)
                {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'k';
            }
            else
            {
                ++emptyCount;
            }
        }
        if (emptyCount > 0)
        {
            fen += std::to_string(emptyCount);
        }
        if (rank > 0)
        {
            fen += '/';
        }
    }

    fen += whiteTurn ? " w " : " b ";

    std::string castling = "";
    if (castlingRights & 0b1000)
        castling += "K";
    if (castlingRights & 0b0100)
        castling += "Q";
    if (castlingRights & 0b0010)
        castling += "k";
    if (castlingRights & 0b0001)
        castling += "q";
    fen += castling.empty() ? "-" : castling;

    fen += " ";
    fen += (enPassantSquare == -1) ? "-" : std::to_string(enPassantSquare);

    return fen;
}