#include "Address.hpp"
#include "DeliveryRequest.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Main function to generate and export randomized delivery data.
 * 
 * This program generates a set of randomized delivery requests, both regular and Prime,
 * and exports them into a CSV file for further use in scheduling and analysis.
 * 
 * @return Exit code (0 for success, non-zero for failure).
 */
int main() {
    std::srand(std::time(0)); ///< Initialize random seed for generating random data

    int numRegularRequests = 500; ///< Number of regular delivery requests
    int numPrimeRequests = 100; ///< Number of Prime delivery requests
    int totalDays = 60; ///< Total number of days for scheduling

    std::vector<DeliveryRequest<double>> deliveries; ///< Vector to store all delivery requests

    // Generate regular delivery requests
    for (int i = 0; i < numRegularRequests; ++i) {
        double x = static_cast<double>(std::rand() % 41) / 10.0; ///< X-coordinate in range [0.0, 4.0]
        double y = static_cast<double>(std::rand() % 41) / 10.0; ///< Y-coordinate in range [0.0, 4.0]
        Address<double> customer(x, y);

        int placementDate = 1 + std::rand() % (totalDays - 7); ///< Placement date in range [1, totalDays-7]
        int earliestDeliveryDate = placementDate + 3; ///< Earliest delivery date (3 days after placement)
        int latestDeliveryDate = placementDate + 7; ///< Latest delivery date (7 days after placement)

        deliveries.emplace_back(customer, placementDate, earliestDeliveryDate, latestDeliveryDate);
    }

    // Generate Prime delivery requests
    for (int i = 0; i < numPrimeRequests; ++i) {
        double x = static_cast<double>(std::rand() % 41) / 10.0; ///< X-coordinate in range [0.0, 4.0]
        double y = static_cast<double>(std::rand() % 41) / 10.0; ///< Y-coordinate in range [0.0, 4.0]
        Address<double> customer(x, y);

        int placementDate = 1 + std::rand() % (totalDays - 1); ///< Placement date in range [1, totalDays-1]
        deliveries.emplace_back(customer, placementDate, placementDate + 1, placementDate + 1, true); ///< Prime delivery
    }

    // Open file for exporting data
    std::ofstream outFile("data/randomized_data.csv");
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for export.\n";
        return 1;
    }

    // Write headers
    outFile << "X,Y,PlacementDate,EarliestDeliveryDate,LatestDeliveryDate,IsPrime\n";

    // Write delivery data to the CSV file
    for (const auto& delivery : deliveries) {
        outFile << delivery.getAddress().getX() << ","
                << delivery.getAddress().getY() << ","
                << delivery.getPlacementDate() << ","
                << delivery.getEarliestDeliveryDate() << ","
                << delivery.getLatestDeliveryDate() << ","
                << (delivery.getIsPrime() ? "1" : "0") << "\n";
    }

    outFile.close();
    std::cout << "Randomized data exported to randomized_data.csv\n";

    return 0;
}
