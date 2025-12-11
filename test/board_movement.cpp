#include "test.h"
#include "chess.hpp"

// movement tests. Tests utilize getMovesForPieceAtPosition, which will 
// implicitly test piece specific movement functions as well
// === PAWN MOVEMENT ===
TEST_XFAIL(pawn_initial_double_move) {
    Board board;
    uint64_t moves = board.getMovesForPieceAtPosition("e2");
    // e3 and e4 should be set
    uint64_t expectedMoves = (1ULL << 20) | (1ULL << 28); // e3 is bit 20, e4 is bit 28
    ASSERT_EQ(expectedMoves, moves);
}
