#ifndef SCHEDULEBALANCED_HPP
#define SCHEDULEBALANCED_HPP

#include "Route.hpp"
#include <map>
#include <fstream>
#include <iomanip>
#include <iostream>

/**
 * @class ScheduleBalanced
 * @brief Manages scheduling with templated routes and addresses.
 * 
 * @tparam T The type of the coordinates in the Address (e.g., int, float, double).
 */
template <typename T>
class ScheduleBalanced {
private:
    std::map<int, Route<T>> dailyRoutes; ///< Map of days to their corresponding routes
    int startDay = 8; ///< Start of the middle-section days
    int endDay = 53; ///< End of the middle-section days
    double redistributionThreshold = 1; ///< Threshold for triggering workload redistribution

public:
    /**
     * @brief Plan routes by assigning deliveries to their best days.
     * 
     * @param deliveryRequests A list of delivery requests to schedule.
     */
    void planRoutes(const std::vector<DeliveryRequest<T>>& deliveryRequests) {
        for (const auto& delivery : deliveryRequests) {
            int bestDay = delivery.getEarliestDeliveryDate();
            dailyRoutes[bestDay].addDelivery(delivery);
        }
    }

    /**
     * @brief Balance the workload by redistributing deliveries across days.
     * 
     * @param depot The location of the depot.
     */
    void balanceWorkload(const Address<T>& depot) {
        bool changesMade = true;

        while (changesMade) {
            changesMade = false;

            int overloadedDay = -1, underloadedDay = -1;
            double maxDistance = -1.0, minDistance = 1e9;

            // Identify overloaded and underloaded days
            for (int day = startDay; day <= endDay; ++day) {
                double dailyDistance = dailyRoutes[day].totalDistance(depot);
                if (dailyDistance > maxDistance) {
                    maxDistance = dailyDistance;
                    overloadedDay = day;
                }
                if (dailyDistance < minDistance) {
                    minDistance = dailyDistance;
                    underloadedDay = day;
                }
            }

            // Compute a dynamic redistribution threshold
            double dynamicThreshold = redistributionThreshold *
                                      ((endDay - underloadedDay + 1.0) / (endDay - startDay + 1.0));

            // Redistribute deliveries if conditions are met
            if (overloadedDay != -1 && underloadedDay != -1 && maxDistance - minDistance > dynamicThreshold) {
                auto& overloadedRoute = dailyRoutes[overloadedDay];
                auto& underloadedRoute = dailyRoutes[underloadedDay];
                auto deliveries = overloadedRoute.getDeliveries();

                for (const auto& delivery : deliveries) {
                    if (delivery.isWithinDeliveryWindow(underloadedDay)) {
                        overloadedRoute.removeDelivery(delivery);
                        underloadedRoute.addDelivery(delivery);
                        changesMade = true;
                        break; // Adjust one delivery at a time
                    }
                }
            }
        }
    }

    /**
     * @brief Optimize all routes to minimize total distance after balancing.
     * 
     * @param depot The location of the depot.
     */
    void optimizeAllRoutes(const Address<T>& depot) {
        double currentTotalDistance = calculateTotalDistance(depot);
        bool changesMade = true;

        while (changesMade) {
            changesMade = false;

            for (auto& [currentDay, route] : dailyRoutes) {
                std::vector<DeliveryRequest<T>> deliveries = route.getDeliveries();

                for (const auto& delivery : deliveries) {
                    int bestDay = currentDay;
                    double bestDistance = currentTotalDistance;

                    for (int day = delivery.getEarliestDeliveryDate(); day <= delivery.getLatestDeliveryDate(); ++day) {
                        if (day == currentDay) continue;

                        // Calculate distances
                        double oldDistance = route.totalDistance(depot);
                        dailyRoutes[day].addDelivery(delivery);
                        double newDistance = dailyRoutes[day].totalDistance(depot);

                        double newTotalDistance = currentTotalDistance - oldDistance + newDistance;

                        if (newTotalDistance < bestDistance) {
                            bestDay = day;
                            bestDistance = newTotalDistance;
                            changesMade = true;
                        }

                        dailyRoutes[day].removeDelivery(delivery);
                    }

                    // Move delivery to the best day
                    if (bestDay != currentDay) {
                        route.removeDelivery(delivery);
                        dailyRoutes[bestDay].addDelivery(delivery);
                        currentTotalDistance = bestDistance;
                    }
                }
            }
        }
    }

    /**
     * @brief Calculate the total distance traveled across all routes.
     * 
     * @param depot The location of the depot.
     * @return The total distance traveled.
     */
    double calculateTotalDistance(const Address<T>& depot) const {
        double totalDistance = 0.0;
        for (const auto& [day, route] : dailyRoutes) {
            totalDistance += route.totalDistance(depot);
        }
        return totalDistance;
    }

    /**
     * @brief Export the schedule to a CSV file.
     * 
     * @param depot The location of the depot.
     * @param filename The name of the output file.
     */
    void exportData(const Address<T>& depot, const std::string& filename) const {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file for export.\n";
            return;
        }

        outFile << "Day,NumDeliveries,TotalDistance\n";
        int totalOrders = 0;
        double totalDistance = 0.0;

        for (const auto& [day, route] : dailyRoutes) {
            int numDeliveries = route.getDeliveries().size();
            double dailyDistance = route.totalDistance(depot);
            totalOrders += numDeliveries;
            totalDistance += dailyDistance;

            outFile << day << "," << numDeliveries << "," << dailyDistance << "\n";
        }

        outFile << "Total," << totalOrders << "," << totalDistance << "\n";
        outFile.close();
    }
};

#endif // SCHEDULEBALANCED_HPP