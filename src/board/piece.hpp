#include "board.hpp"
#include <cstdint>
#ifndef PIECE_HPP
#define PIECE_HPP

class Piece {
    private:
        bool white;
    public:
        Piece(bool isWhite);
        /**:
         * Takes an instance of Board and returns a bitmap of all legal move positions 
         **/
        uint64_t getLegalMoves(Board board, uint64_t position);
        bool isWhite() {
            return this->white;
        }
};
#endif