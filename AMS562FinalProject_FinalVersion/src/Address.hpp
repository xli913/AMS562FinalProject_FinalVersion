#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <cmath>

/**
 * @class Address
 * @brief Represents a geographical address with coordinates of generic type.
 * 
 * @tparam T The type of the coordinates (e.g., int, float, double).
 */
template <typename T>
class Address {
private:
    T x; ///< X-coordinate of the address
    T y; ///< Y-coordinate of the address

public:
    /**
     * @brief Constructor to initialize an address with coordinates.
     * 
     * @param xCoord The X-coordinate of the address.
     * @param yCoord The Y-coordinate of the address.
     */
    Address(T xCoord, T yCoord) : x(xCoord), y(yCoord) {}

    /**
     * @brief Get the X-coordinate of the address.
     * 
     * @return The X-coordinate.
     */
    T getX() const { return x; }

    /**
     * @brief Get the Y-coordinate of the address.
     * 
     * @return The Y-coordinate.
     */
    T getY() const { return y; }

    /**
     * @brief Calculate the Euclidean distance to another address.
     * 
     * @param other The other address to calculate the distance to.
     * @return The Euclidean distance to the other address.
     */
    double distanceTo(const Address<T>& other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }
};

#endif // ADDRESS_HPP