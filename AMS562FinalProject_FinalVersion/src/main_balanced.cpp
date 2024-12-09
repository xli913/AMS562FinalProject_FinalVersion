#include "Address.hpp"
#include "DeliveryRequest.hpp"
#include "Route.hpp"
#include "ScheduleBalanced.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Helper function to load delivery requests from a CSV file.
 * 
 * @param filename The name of the input CSV file.
 * @param regularDeliveries A vector to store regular delivery requests.
 * @param primeDeliveries A vector to store Prime delivery requests.
 */
void loadDeliveriesFromCSV(
    const std::string& filename,
    std::vector<DeliveryRequest<double>>& regularDeliveries,
    std::vector<DeliveryRequest<double>>& primeDeliveries) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error opening input file: " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the header
    std::getline(inFile, line);

    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string value;
        double x, y;
        int placementDate, earliest, latest;
        bool isPrime;

        // Parse values from the CSV
        std::getline(ss, value, ',');
        x = std::stod(value);

        std::getline(ss, value, ',');
        y = std::stod(value);

        std::getline(ss, value, ',');
        placementDate = std::stoi(value);

        std::getline(ss, value, ',');
        earliest = std::stoi(value);

        std::getline(ss, value, ',');
        latest = std::stoi(value);

        std::getline(ss, value, ',');
        isPrime = (value == "1");

        Address<double> customer(x, y);
        DeliveryRequest<double> delivery(customer, placementDate, earliest, latest, isPrime);

        // Separate into regular and Prime deliveries
        if (isPrime) {
            primeDeliveries.push_back(delivery);
        } else {
            regularDeliveries.push_back(delivery);
        }
    }

    inFile.close();
}

/**
 * @brief Main function to schedule and balance deliveries using input data.
 * 
 * This function loads delivery requests from a CSV file, processes them into two categories 
 * (regular and Prime deliveries), and schedules and balances the deliveries. The results 
 * are exported to separate CSV files for analysis.
 * 
 * @return Exit code (0 for success).
 */
int main() {
    Address<double> depot(0.0, 0.0); ///< The depot location

    std::vector<DeliveryRequest<double>> regularDeliveries; ///< Vector to store regular deliveries
    std::vector<DeliveryRequest<double>> primeDeliveries; ///< Vector to store Prime deliveries

    // Load deliveries from the exported CSV file
    const std::string inputFile = "data/randomized_data_large.csv";
    loadDeliveriesFromCSV(inputFile, regularDeliveries, primeDeliveries);

    // Regular Customers Schedule
    ScheduleBalanced<double> regularSchedule;
    regularSchedule.planRoutes(regularDeliveries);
    regularSchedule.optimizeAllRoutes(depot);
    regularSchedule.balanceWorkload(depot);
    regularSchedule.exportData(depot, "results/regular_customers_balanced_large.csv");

    // Combined Regular + Prime Customers Schedule
    ScheduleBalanced<double> combinedSchedule;
    combinedSchedule.planRoutes(regularDeliveries);
    combinedSchedule.planRoutes(primeDeliveries);
    combinedSchedule.optimizeAllRoutes(depot);
    combinedSchedule.balanceWorkload(depot);
    combinedSchedule.exportData(depot, "results/combined_customers_balanced_large.csv");

    return 0;
}