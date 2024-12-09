#include <gtest/gtest.h>
#include "Address.hpp"

// Test constructor and getters
TEST(AddressTest, ConstructorAndGetters) {
    Address<double> addr(3.0, 4.0);
    EXPECT_DOUBLE_EQ(addr.getX(), 3.0);
    EXPECT_DOUBLE_EQ(addr.getY(), 4.0);
}

// Test distance calculation
TEST(AddressTest, DistanceCalculation) {
    Address<double> addr1(0.0, 0.0);
    Address<double> addr2(3.0, 4.0);
    EXPECT_DOUBLE_EQ(addr1.distanceTo(addr2), 5.0);
}

// Test distance calculation with same point
TEST(AddressTest, DistanceToSamePoint) {
    Address<double> addr1(3.0, 4.0);
    EXPECT_DOUBLE_EQ(addr1.distanceTo(addr1), 0.0);
}

// Test distance with large coordinates
TEST(AddressTest, DistanceLargeCoordinates) {
    Address<double> addr1(1e6, 1e6);
    Address<double> addr2(-1e6, -1e6);
    EXPECT_DOUBLE_EQ(addr1.distanceTo(addr2), 2.82842712474619e6);
}

// Test negative coordinates
TEST(AddressTest, NegativeCoordinates) {
    Address<double> addr1(-3.0, -4.0);
    Address<double> addr2(-6.0, -8.0);
    EXPECT_DOUBLE_EQ(addr1.distanceTo(addr2), 5.0);
}
