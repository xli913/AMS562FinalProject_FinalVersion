#ifndef DELIVERYREQUEST_HPP
#define DELIVERYREQUEST_HPP

#include "Address.hpp"

/**
 * @class DeliveryRequest
 * @brief Represents a customer's delivery order with a templated Address.
 * 
 * @tparam T The type of the coordinates in the Address (e.g., int, float, double).
 */
template <typename T>
class DeliveryRequest {
private:
    Address<T> address; ///< The delivery address
    int placementDate; ///< The date the delivery was placed
    int earliestDeliveryDate; ///< The earliest possible delivery date
    int latestDeliveryDate; ///< The latest possible delivery date
    bool isPrime; ///< Whether the delivery is for a Prime customer

public:
    /**
     * @brief Constructor to initialize a delivery request.
     * 
     * @param addr The delivery address.
     * @param placeDate The date the delivery was placed.
     * @param earliest The earliest possible delivery date (ignored for Prime customers).
     * @param latest The latest possible delivery date (ignored for Prime customers).
     * @param prime Whether the delivery is for a Prime customer (default is false).
     */
    DeliveryRequest(const Address<T>& addr, int placeDate, int earliest, int latest, bool prime = false)
        : address(addr), placementDate(placeDate), isPrime(prime) {
        if (isPrime) {
            earliestDeliveryDate = placeDate + 1;
            latestDeliveryDate = placeDate + 1;
        } else {
            earliestDeliveryDate = earliest;
            latestDeliveryDate = latest;
        }
    }

    /**
     * @brief Get the delivery address.
     * 
     * @return The delivery address.
     */
    Address<T> getAddress() const { return address; }

    /**
     * @brief Get the placement date of the delivery.
     * 
     * @return The placement date.
     */
    int getPlacementDate() const { return placementDate; }

    /**
     * @brief Get the earliest delivery date.
     * 
     * @return The earliest delivery date.
     */
    int getEarliestDeliveryDate() const { return earliestDeliveryDate; }

    /**
     * @brief Get the latest delivery date.
     * 
     * @return The latest delivery date.
     */
    int getLatestDeliveryDate() const { return latestDeliveryDate; }

    /**
     * @brief Check if a given day is within the delivery window.
     * 
     * @param day The day to check.
     * @return True if the day is within the delivery window, false otherwise.
     */
    bool isWithinDeliveryWindow(int day) const {
        return day >= earliestDeliveryDate && day <= latestDeliveryDate;
    }

    /**
     * @brief Compare two delivery requests for equality.
     * 
     * @param other The other delivery request to compare with.
     * @return True if the two requests are equal, false otherwise.
     */
    bool operator==(const DeliveryRequest<T>& other) const {
        return address.getX() == other.address.getX() &&
               address.getY() == other.address.getY() &&
               placementDate == other.placementDate &&
               earliestDeliveryDate == other.earliestDeliveryDate &&
               latestDeliveryDate == other.latestDeliveryDate &&
               isPrime == other.isPrime;
    }
};

#endif // DELIVERYREQUEST_HPP