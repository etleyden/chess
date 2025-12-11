#include "board.hpp"
#include <stdexcept>

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