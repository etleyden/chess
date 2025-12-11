#include "board.hpp"

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