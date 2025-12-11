#include "test.h"
#include "chess.hpp"

static void assert_initial_positions(Board board) {
    ASSERT_EQ(Board::Piece::WHITE_PAWN, board.getPieceAtPosition("a2"));
    ASSERT_EQ(Board::Piece::WHITE_KNIGHT, board.getPieceAtPosition("b1"));
    ASSERT_EQ(Board::Piece::WHITE_BISHOP, board.getPieceAtPosition("c1"));
    ASSERT_EQ(Board::Piece::WHITE_ROOK, board.getPieceAtPosition("a1"));
    ASSERT_EQ(Board::Piece::WHITE_QUEEN, board.getPieceAtPosition("d1"));
    ASSERT_EQ(Board::Piece::WHITE_KING, board.getPieceAtPosition("e1"));
    ASSERT_EQ(Board::Piece::BLACK_PAWN, board.getPieceAtPosition("a7"));
    ASSERT_EQ(Board::Piece::BLACK_KNIGHT, board.getPieceAtPosition("b8"));
    ASSERT_EQ(Board::Piece::BLACK_BISHOP, board.getPieceAtPosition("c8"));
    ASSERT_EQ(Board::Piece::BLACK_ROOK, board.getPieceAtPosition("a8"));
    ASSERT_EQ(Board::Piece::BLACK_QUEEN, board.getPieceAtPosition("d8"));
    ASSERT_EQ(Board::Piece::BLACK_KING, board.getPieceAtPosition("e8"));
}

TEST(initialize_board) {
    Board board;
    std::string expectedBoard =
        "rnbqkbnr\n"
        "pppppppp\n"
        "X X X X \n"
        " X X X X\n"
        "X X X X \n"
        " X X X X\n"
        "PPPPPPPP\n"
        "RNBQKBNR\n";
    ASSERT_EQ(expectedBoard, board.boardToString());
}
TEST(generateFEN_initial_board) {
    Board board;
    std::string expectedFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
    ASSERT_EQ(expectedFEN, board.generateFEN());
}

TEST(getPieceAtPosition_initial_positions)
{
    Board board;
    assert_initial_positions(board);
}
// FEN Spec https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
TEST(fen_notation_board_initial) {
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
    Board board(fen);
    std::cout << "Generated Board:\n" << board.boardToString() << std::endl;
    assert_initial_positions(board);
}
TEST(fen_notation_1_e4) {
    std::string fen = "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3";
    Board board(fen);
    ASSERT_EQ(Board::Piece::EMPTY, board.getPieceAtPosition("e2"));
    ASSERT_EQ(Board::Piece::WHITE_PAWN, board.getPieceAtPosition("e4"));
}
TEST(fen_notation_1_c5) {
    std::string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2";
    Board board(fen);
    ASSERT_EQ(Board::Piece::EMPTY, board.getPieceAtPosition("e2"));
    ASSERT_EQ(Board::Piece::WHITE_PAWN, board.getPieceAtPosition("e4"));
    ASSERT_EQ(Board::Piece::EMPTY, board.getPieceAtPosition("c7"));
    ASSERT_EQ(Board::Piece::BLACK_PAWN, board.getPieceAtPosition("c5"));
}
TEST(fen_notation_2_Nf3) {
    std::string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
    Board board(fen);
    ASSERT_EQ(Board::Piece::EMPTY, board.getPieceAtPosition("e2"));
    ASSERT_EQ(Board::Piece::WHITE_PAWN, board.getPieceAtPosition("e4"));
    ASSERT_EQ(Board::Piece::EMPTY, board.getPieceAtPosition("c7"));
    ASSERT_EQ(Board::Piece::BLACK_PAWN, board.getPieceAtPosition("c5"));
    ASSERT_EQ(Board::Piece::EMPTY, board.getPieceAtPosition("g1"));
    ASSERT_EQ(Board::Piece::WHITE_KNIGHT, board.getPieceAtPosition("f3"));
}