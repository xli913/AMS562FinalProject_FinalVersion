#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "DeliveryRequest.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

/**
 * @class Route
 * @brief Represents a delivery route for a single day, with templated DeliveryRequest.
 * 
 * @tparam T The type of the coordinates in the Address (e.g., int, float, double).
 */
template <typename T>
class Route {
private:
    std::vector<DeliveryRequest<T>> deliveries; ///< List of delivery requests for the route

public:
    /**
     * @brief Add a delivery request to the route.
     * 
     * @param delivery The delivery request to add.
     */
    void addDelivery(const DeliveryRequest<T>& delivery) {
        deliveries.push_back(delivery);
    }

    /**
     * @brief Remove a delivery request from the route.
     * 
     * @param delivery The delivery request to remove.
     */
    void removeDelivery(const DeliveryRequest<T>& delivery) {
        deliveries.erase(std::remove(deliveries.begin(), deliveries.end(), delivery), deliveries.end());
    }

    /**
     * @brief Calculate the total distance of the route, starting and ending at the depot.
     * 
     * @param depot The starting and ending location of the route.
     * @return The total distance of the route.
     */
    double totalDistance(const Address<T>& depot) const {
        if (deliveries.empty()) return 0.0;

        double distance = 0.0;
        Address<T> currentLocation = depot;

        for (const auto& delivery : deliveries) {
            distance += currentLocation.distanceTo(delivery.getAddress());
            currentLocation = delivery.getAddress();
        }

        distance += currentLocation.distanceTo(depot); // Return to depot
        return distance;
    }

    /**
     * @brief Get the list of deliveries in the route.
     * 
     * @return A vector of delivery requests.
     */
    std::vector<DeliveryRequest<T>> getDeliveries() const {
        return deliveries;
    }

    /**
     * @brief Print the details of the route for a given day.
     * 
     * @param day The day number associated with the route.
     */
    void printRoute(int day) const {
        std::cout << "Day " << day << ": " << deliveries.size() << " deliveries\n";
        for (const auto& delivery : deliveries) {
            std::cout << " - Address(" << delivery.getAddress().getX()
                      << ", " << delivery.getAddress().getY() << ")";
        }
        std::cout << std::endl;
    }
};

#endif // ROUTE_HPP