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
    enum Piece {
        WHITE_PAWN,
        WHITE_KNIGHT,
        WHITE_BISHOP,
        WHITE_ROOK,
        WHITE_QUEEN,
        WHITE_KING,
        BLACK_PAWN,
        BLACK_KNIGHT,
        BLACK_BISHOP,
        BLACK_ROOK,
        BLACK_QUEEN,
        BLACK_KING
    };
    uint64_t pieces[12];
    // special rules
    bool whiteTurn; // is it white's turn?
    int castlingRights;  // can anyone castle?
    int enPassantSquare; // which squares are valid en passant squares

    public:  
    /**
     * @brief Constructs a new Board object with all pieces in their initial positions.
     * 
     * Initializes the board with white and black pieces in their starting positions,
     * sets the turn to white, enables castling rights, and sets no en passant square.
     */
    Board();
    uint64_t getMovesForPieceAtPosition(std::string position);
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

    /**
     * @brief Generates a string representation of the current board state.
     * 
     * Uses the following characters to represent the board:
     * - Empty dark space: '_'
     * - Empty light space: 'O'
     * - White pieces: uppercase (P, N, B, R, Q, K)
     * - Black pieces: lowercase (p, n, b, r, q, k)
     * 
     * @return std::string The string representation of the board.
     */
    std::string boardToString() const;
    /**
     * @brief Generates the FEN representation of the current board state.
     * 
     * Read more: https://www.chess.com/terms/fen-chess
     * 
     * @return std::string The FEN string representing the board.
     */
    std::string generateFEN() const;
    private:
    // bitmask utility functions    
    uint64_t getBitmaskForPosition(std::string position);
    uint64_t getBitmaskForRow(int row);
    uint64_t getBitmaskForColumn(char column);
    uint64_t getBitmaskForColumn(int column);
};