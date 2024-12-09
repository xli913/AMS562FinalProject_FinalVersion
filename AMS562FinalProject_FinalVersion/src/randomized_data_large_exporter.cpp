#include "Address.hpp"
#include "DeliveryRequest.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Main function to generate and export large randomized delivery data.
 * 
 * This program generates a large dataset of delivery requests for both regular and special days.
 * It exports the generated data into a CSV file for use in scheduling and analysis.
 * 
 * @return Exit code (0 for success, non-zero for failure).
 */
int main() {
    std::srand(std::time(0)); ///< Initialize random seed for generating random data

    int totalDays = 360; ///< Total number of days in the dataset

    int numRegularDays = 330; ///< Number of regular days
    int regularRequestsPerRegularDay = 2750 / numRegularDays; ///< Regular requests per regular day
    int primeRequestsPerRegularDay = 550 / numRegularDays; ///< Prime requests per regular day

    int numSpecialDays = 30; ///< Number of special days
    int regularRequestsPerSpecialDay = 600 / numSpecialDays; ///< Regular requests per special day
    int primeRequestsPerSpecialDay = 120 / numSpecialDays; ///< Prime requests per special day

    std::vector<DeliveryRequest<double>> deliveries; ///< Vector to store all delivery requests

    // Generate delivery requests for regular days
    for (int day = 1; day <= numRegularDays; ++day) {
        // Generate regular requests
        for (int i = 0; i < regularRequestsPerRegularDay; ++i) {
            double x = static_cast<double>(std::rand() % 41) / 10.0; ///< X-coordinate in range [0.0, 4.0]
            double y = static_cast<double>(std::rand() % 41) / 10.0; ///< Y-coordinate in range [0.0, 4.0]
            Address customer(x, y);

            int placementDate = day;
            int earliestDeliveryDate = placementDate + 3;
            int latestDeliveryDate = placementDate + 7;

            deliveries.emplace_back(customer, placementDate, earliestDeliveryDate, latestDeliveryDate);
        }

        // Generate Prime requests
        for (int i = 0; i < primeRequestsPerRegularDay; ++i) {
            double x = static_cast<double>(std::rand() % 41) / 10.0; ///< X-coordinate in range [0.0, 4.0]
            double y = static_cast<double>(std::rand() % 41) / 10.0; ///< Y-coordinate in range [0.0, 4.0]
            Address customer(x, y);

            int placementDate = day;
            deliveries.emplace_back(customer, placementDate, placementDate + 1, placementDate + 1, true);
        }
    }

    // Generate delivery requests for special days
    for (int day = numRegularDays + 1; day <= totalDays; ++day) {
        // Generate regular requests
        for (int i = 0; i < regularRequestsPerSpecialDay; ++i) {
            double x = static_cast<double>(std::rand() % 41) / 10.0; ///< X-coordinate in range [0.0, 4.0]
            double y = static_cast<double>(std::rand() % 41) / 10.0; ///< Y-coordinate in range [0.0, 4.0]
            Address customer(x, y);

            int placementDate = day;
            int earliestDeliveryDate = placementDate + 3;
            int latestDeliveryDate = placementDate + 7;

            deliveries.emplace_back(customer, placementDate, earliestDeliveryDate, latestDeliveryDate);
        }

        // Generate Prime requests
        for (int i = 0; i < primeRequestsPerSpecialDay; ++i) {
            double x = static_cast<double>(std::rand() % 41) / 10.0; ///< X-coordinate in range [0.0, 4.0]
            double y = static_cast<double>(std::rand() % 41) / 10.0; ///< Y-coordinate in range [0.0, 4.0]
            Address customer(x, y);

            int placementDate = day;
            deliveries.emplace_back(customer, placementDate, placementDate + 1, placementDate + 1, true);
        }
    }

    // Open file for exporting data
    std::ofstream outFile("data/randomized_data_large.csv");
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
    std::cout << "Randomized large data exported to data/randomized_data_large.csv\n";

    return 0;
}