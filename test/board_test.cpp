#include "test.h"
#include "chess.hpp"

TEST(compareRow_match) {
    ASSERT_EQ(1, Board::compareRow("e4", "4"));
}
int main() {
    return RUN_ALL_TESTS();
}