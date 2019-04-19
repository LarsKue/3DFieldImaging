//
// Created by Lars on 15/04/2019.
//

#ifndef ELECTRICFIELD_POINT_H
#define ELECTRICFIELD_POINT_H

#include <cmath> // pow

/**
 * \brief A 3-dimensional Point
 */
template<typename value_type = double>
struct Point {

    Point() = default;
    Point(value_type mX, value_type mY, value_type mZ) : x(mX), y(mY), z(mZ) {}

    template<typename other_value_type>
    value_type sq_distance_to(const Point<other_value_type>& other) const {
        return static_cast<value_type>(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2));
    }

    value_type x = 0;
    value_type y = 0;
    value_type z = 0;

};


#endif //ELECTRICFIELD_POINT_H
