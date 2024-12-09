#include <gtest/gtest.h>
#include "Route.hpp"

// Test adding and removing deliveries
TEST(RouteTest, AddRemoveDelivery) {
    Address<double> depot(0.0, 0.0);
    Address<double> addr1(1.0, 1.0);
    DeliveryRequest<double> request1(addr1, 1, 3, 7);

    Route<double> route;
    route.addDelivery(request1);
    EXPECT_EQ(route.getDeliveries().size(), 1);

    route.removeDelivery(request1);
    EXPECT_EQ(route.getDeliveries().size(), 0);
}

// Test total distance calculation
TEST(RouteTest, TotalDistance) {
    Address<double> depot(0.0, 0.0);
    Address<double> addr1(3.0, 4.0);
    Address<double> addr2(6.0, 8.0);

    DeliveryRequest<double> request1(addr1, 1, 3, 7);
    DeliveryRequest<double> request2(addr2, 1, 3, 7);

    Route<double> route;
    route.addDelivery(request1);
    route.addDelivery(request2);

    double expectedDistance = 5.0 + 5.0 + 10.0; // Depot to addr1, addr1 to addr2, addr2 to depot
    EXPECT_DOUBLE_EQ(route.totalDistance(depot), expectedDistance);
}

// Test empty route distance
TEST(RouteTest, EmptyRoute) {
    Address<double> depot(0.0, 0.0);
    Route<double> route;

    EXPECT_DOUBLE_EQ(route.totalDistance(depot), 0.0);
}
