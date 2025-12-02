#include <stdexcept>
#include "board.hpp"

Board::Board()
    : whitePawns(0x000000000000FF00),
      whiteKnights(0x0000000000000042),
      whiteBishops(0x0000000000000024),
      whiteRooks(0x0000000000000081),
      whiteQueens(0x0000000000000008),
      whiteKing(0x0000000000000010),
      blackPawns(0x00FF000000000000),
      blackKnights(0x4200000000000000),
      blackBishops(0x2400000000000000),
      blackRooks(0x8100000000000000),
      blackQueens(0x0800000000000000),
      blackKing(0x1000000000000000),
      whiteTurn(true),
      castlingRights(0b1111), // Both sides can castle both ways initially
      enPassantSquare(-1) // No en passant square initially
{
    // Constructor body can remain empty as initialization is done in the initializer list
}

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
    if(position.length() < 2) {
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

std::string Board::boardToString() const
{
    std::string boardRepresentation;
    for (int row = 7; row >= 0; --row) {
        for (int col = 0; col < 8; ++col) {
            uint64_t square = 1ULL << (row * 8 + col);

            if (whitePawns & square) {
                boardRepresentation += 'P';
            } else if (whiteKnights & square) {
                boardRepresentation += 'N';
            } else if (whiteBishops & square) {
                boardRepresentation += 'B';
            } else if (whiteRooks & square) {
                boardRepresentation += 'R';
            } else if (whiteQueens & square) {
                boardRepresentation += 'Q';
            } else if (whiteKing & square) {
                boardRepresentation += 'K';
            } else if (blackPawns & square) {
                boardRepresentation += 'p';
            } else if (blackKnights & square) {
                boardRepresentation += 'n';
            } else if (blackBishops & square) {
                boardRepresentation += 'b';
            } else if (blackRooks & square) {
                boardRepresentation += 'r';
            } else if (blackQueens & square) {
                boardRepresentation += 'q';
            } else if (blackKing & square) {
                boardRepresentation += 'k';
            } else {
                // Determine if the square is light or dark
                if ((row + col) % 2 == 1) {
                    boardRepresentation += 'X';
                } else {
                    boardRepresentation += ' ';
                }
            }
        }
        boardRepresentation += '\n'; // Newline after each row
    }
    return boardRepresentation;
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

std::string Board::generateFEN() const {
    std::string fen;
    for (int rank = 7; rank >= 0; --rank) {
        int emptyCount = 0;
        for (int file = 0; file < 8; ++file) {
            uint64_t square = 1ULL << (rank * 8 + file);
            if (whitePawns & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'P';
            } else if (whiteKnights & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'N';
            } else if (whiteBishops & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'B';
            } else if (whiteRooks & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'R';
            } else if (whiteQueens & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'Q';
            } else if (whiteKing & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'K';
            } else if (blackPawns & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'p';
            } else if (blackKnights & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'n';
            } else if (blackBishops & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'b';
            } else if (blackRooks & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'r';
            } else if (blackQueens & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'q';
            } else if (blackKing & square) {
                if (emptyCount > 0) {
                    fen += std::to_string(emptyCount);
                    emptyCount = 0;
                }
                fen += 'k';
            } else {
                ++emptyCount;
            }
        }
        if (emptyCount > 0) {
            fen += std::to_string(emptyCount);
        }
        if (rank > 0) {
            fen += '/';
        }
    }

    fen += whiteTurn ? " w " : " b ";

    std::string castling = "";
    if (castlingRights & 0b1000) castling += "K";
    if (castlingRights & 0b0100) castling += "Q";
    if (castlingRights & 0b0010) castling += "k";
    if (castlingRights & 0b0001) castling += "q";
    fen += castling.empty() ? "-" : castling;

    fen += " ";
    fen += (enPassantSquare == -1) ? "-" : std::to_string(enPassantSquare);

    return fen;
}