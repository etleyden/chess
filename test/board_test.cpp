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
int main() {
    return RUN_ALL_TESTS();
}