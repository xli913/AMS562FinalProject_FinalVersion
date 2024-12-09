#include <gtest/gtest.h>
#include "DeliveryRequest.hpp"

// Test constructor and getters
TEST(DeliveryRequestTest, ConstructorAndGetters) {
    Address<double> addr(3.0, 4.0);
    DeliveryRequest<double> request(addr, 1, 3, 7);

    EXPECT_DOUBLE_EQ(request.getAddress().getX(), 3.0);
    EXPECT_DOUBLE_EQ(request.getAddress().getY(), 4.0);
    EXPECT_EQ(request.getPlacementDate(), 1);
    EXPECT_EQ(request.getEarliestDeliveryDate(), 3);
    EXPECT_EQ(request.getLatestDeliveryDate(), 7);
}

// Test Prime member logic
TEST(DeliveryRequestTest, PrimeLogic) {
    Address<double> addr(3.0, 4.0);
    DeliveryRequest<double> primeRequest(addr, 1, 0, 0, true);

    EXPECT_EQ(primeRequest.getEarliestDeliveryDate(), 2); // Next day delivery
    EXPECT_EQ(primeRequest.getLatestDeliveryDate(), 2);   // Same as earliest
    EXPECT_TRUE(primeRequest.getIsPrime());
}

// Test with same earliest and latest delivery dates
TEST(DeliveryRequestTest, SameEarliestLatestDates) {
    Address<double> addr(1.0, 2.0);
    DeliveryRequest<double> request(addr, 1, 3, 3);

    EXPECT_EQ(request.getEarliestDeliveryDate(), 3);
    EXPECT_EQ(request.getLatestDeliveryDate(), 3);
    EXPECT_TRUE(request.isWithinDeliveryWindow(3));
    EXPECT_FALSE(request.isWithinDeliveryWindow(2));
}

// Test edge case: delivery window before placement date
TEST(DeliveryRequestTest, DeliveryWindowBeforePlacement) {
    Address<double> addr(1.0, 2.0);
    DeliveryRequest<double> request(addr, 5, 3, 4);

    EXPECT_EQ(request.getEarliestDeliveryDate(), 3);
    EXPECT_EQ(request.getLatestDeliveryDate(), 4);
    EXPECT_FALSE(request.isWithinDeliveryWindow(5));
}

