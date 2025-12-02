#pragma once

#include <vector>
#include <string>
#include <cstdint>

class Board {
    // 64 bit representation of where each of
    // these piece types are on the board.
    uint64_t whitePawns;
    uint64_t whiteKnights;
    uint64_t whiteBishops;
    uint64_t whiteQueens;
    uint64_t whiteKing;
    uint64_t blackPawns;
    uint64_t blackKnights;
    uint64_t blackBishops;
    uint64_t blackQueens;
    uint64_t blackKing;
    // special rules
    bool whiteTurn;      // who's turn is it?
    int castlingRights;  // can anyone castle?
    int enPassantSquare; // which squares are valid en passant squares

    public: 
    /**
     * Given an input position (e.g. "e4") and a target row (e.g. "4"),
     * return -1 if the position is above the row, 0 if it's on the row,
     * and 1 if it's below the row. row can be a string or an integer
     */
        static int compareRow(std::string position, std::string targetRow);
        static int compareRow(std::string position, int targetRow);
        std::vector<std::string> generateMoves();
};