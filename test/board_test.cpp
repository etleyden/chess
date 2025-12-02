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
int main() {
    return RUN_ALL_TESTS();
}