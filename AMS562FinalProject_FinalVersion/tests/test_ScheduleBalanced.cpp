#include <gtest/gtest.h>
#include "ScheduleBalanced.hpp"

// Test planning and balancing deliveries
TEST(ScheduleBalancedTest, PlanAndBalanceDeliveries) {
    Address<double> depot(0.0, 0.0);

    Address<double> addr1(1.0, 1.0);
    Address<double> addr2(2.0, 2.0);
    DeliveryRequest<double> request1(addr1, 1, 3, 7);
    DeliveryRequest<double> request2(addr2, 1, 3, 7);

    ScheduleBalanced<double> schedule;
    std::vector<DeliveryRequest<double>> requests = {request1, request2};
    schedule.planRoutes(requests);

    EXPECT_EQ(schedule.calculateTotalDistance(depot), 2 * depot.distanceTo(addr1) + depot.distanceTo(addr2));
}

// Test balancing empty schedule
TEST(ScheduleBalancedTest, EmptySchedule) {
    Address<double> depot(0.0, 0.0);
    ScheduleBalanced<double> schedule;

    schedule.balanceWorkload(depot);
    EXPECT_EQ(schedule.calculateTotalDistance(depot), 0.0);
}

// Test edge case: all deliveries on the same day
TEST(ScheduleBalancedTest, SingleDayDeliveries) {
    Address<double> depot(0.0, 0.0);

    Address<double> addr1(1.0, 1.0);
    Address<double> addr2(2.0, 2.0);
    DeliveryRequest<double> request1(addr1, 1, 1, 1);
    DeliveryRequest<double> request2(addr2, 1, 1, 1);

    ScheduleBalanced<double> schedule;
    std::vector<DeliveryRequest<double>> requests = {request1, request2};
    schedule.planRoutes(requests);

    EXPECT_EQ(schedule.calculateTotalDistance(depot), depot.distanceTo(addr1) + addr1.distanceTo(addr2) + addr2.distanceTo(depot));
}
