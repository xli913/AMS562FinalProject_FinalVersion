#include <gtest/gtest.h>

/**
 * @brief Entry point for Google Test.
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
