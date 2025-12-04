#include "test.h"
#include "chess.hpp"

TEST(compareRow_match) {
    ASSERT_EQ(0, Board::compareRow("e4", "4"));
}
TEST(compareRow_above) {
    ASSERT_GT(0, Board::compareRow("e5", "6"));
}
TEST(compareRow_below) {
    ASSERT_LT(0, Board::compareRow("e2", "1"));
}
TEST(compareRow_invalid_position_high) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareRow("e9", "4");
    });
}
TEST(compareRow_invalid_position_low) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareRow("e0", "4");
    });
}
TEST(compareRow_invalid_target_high) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareRow("e4", "9");
    });
}
TEST(compareRow_invalid_target_low) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareRow("e4", "0");
    });
}
TEST(compareRow_int_match) {
    ASSERT_EQ(0, Board::compareRow("e4", 4));
}
TEST(compareRow_int_above) {
    ASSERT_GT(0, Board::compareRow("e5", 6));
}
TEST(compareRow_int_below) {
    ASSERT_LT(0, Board::compareRow("e2", 1));
}
TEST(compareColumn_match) {
    ASSERT_EQ(0, Board::compareColumn("e4", 'e'));
}
TEST(compareColumn_right) {
    ASSERT_GT(0, Board::compareColumn("f4", 'g'));
}
TEST(compareColumn_left) {
    ASSERT_LT(0, Board::compareColumn("d4", 'c'));
}
TEST(compareColumn_invalid_position_high) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareColumn("i4", 'e');
    });
}
TEST(compareColumn_invalid_position_low) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareColumn("`4", '0');
    });
}
TEST(compareColumn_invalid_target_high) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareColumn("e4", 'z');
    });
}
TEST(compareColumn_invalid_target_low) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareColumn("e4", '`');
    });
}
TEST(compareColumn_int_match) {
    ASSERT_EQ(0, Board::compareColumn("e4", 5));
}
TEST(compareColumn_int_right) {
    ASSERT_GT(0, Board::compareColumn("f4", 7));
}
TEST(compareColumn_int_left) {
    ASSERT_LT(0, Board::compareColumn("d4", 3));
}
TEST(compareColumn_int_invalid_position_high) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareColumn("i4", 5);
    });
}
TEST(compareColumn_int_invalid_position_low) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareColumn("`4", 0);
    });
}
TEST(compareColumn_int_invalid_target_high) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareColumn("e4", 9);
    });
}
TEST(compareColumn_int_invalid_target_low) {
    ASSERT_THROWS(std::invalid_argument, []() {
        Board::compareColumn("e4", 0);
    });
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
TEST(getPieceAtPosition_initial_positions) {
    Board board;
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
int main() {
    return RUN_ALL_TESTS();
}