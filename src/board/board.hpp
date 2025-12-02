#pragma once

#include <vector>
#include <string>
#include <cstdint>

/**
 * @brief Represents a chessboard.
 * 
 * The Board class manages the state of a chessboard, including the positions
 * of pieces, turn management, and special rules like castling and en passant.
 */
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
    /**
     * @brief Indicates whether it is white's turn.
     */
    bool whiteTurn;
    /**
     * @brief Indicates whether castling is allowed.
     */
    int castlingRights;  // can anyone castle?
    int enPassantSquare; // which squares are valid en passant squares

    public: 
    /**
     * @brief Compares two rows on the chessboard.
     * 
     * This function takes a position and a target row and compares their row values.
     * 
     * @param position The position string (e.g., "e4").
     * @param targetRow The target row string (e.g., "4").
     * @return int The difference between the row of the position and the target row.
     * @throws std::invalid_argument If the input strings are invalid.
     */
    static int compareRow(std::string position, std::string targetRow);
    static int compareRow(std::string position, int targetRow);
    /**
     * @brief Calculates the distance between a position's column and a target column.
     * 
     * Given an input position (e.g., "e4") and a target column (e.g., 'e' or 5),
     * this function returns the distance between the position's column and the target column.
     * 
     * A positive value means the position is to the right of the target column,
     * a negative value means it's to the left, and zero means they are the same.
     */
    static int compareColumn(std::string position, char targetColumn);
    static int compareColumn(std::string position, int targetColumn);
};