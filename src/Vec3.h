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
struct Vec3 {

    /// Constructors ///
    Vec3() = default;
    Vec3(value_type mX, value_type mY, value_type mZ) : x(mX), y(mY), z(mZ) {}

    /// Operators ///

    Vec3<value_type> operator+() const {
        return *this;
    }

    Vec3<value_type> operator-() const {
        return Vec3<value_type>(-x, -y, -z);
    }

    // henceforth: ovt = other value type
    template<typename ovt>
    Vec3<value_type>& operator+=(const Vec3<ovt>& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    template<typename ovt>
    Vec3<value_type>& operator-=(const Vec3<ovt>& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // vectorial multiplication never yields another vector
    template<typename ovt>
    Vec3<value_type>& operator*=(const Vec3<ovt>& other) = delete;

    // scalar multiplication
    template<typename ovt>
    Vec3<value_type>& operator*=(const ovt& other) {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }

    // vectorial division does not exist
    template<typename ovt>
    Vec3<value_type>& operator/=(const Vec3<ovt>& other) = delete;

    // scalar division
    template<typename ovt>
    Vec3<value_type>& operator/=(const ovt& other) {
        x /= other;
        y /= other;
        z /= other;
        return *this;
    }

    template<typename ovt>
    Vec3<value_type> operator+(const Vec3<ovt>& other) const {
        Vec3<value_type> result = *this;
        result += other;
        return result;
    }

    template<typename ovt>
    Vec3<value_type> operator-(const Vec3<ovt>& other) const {
        Vec3<value_type> result = *this;
        result -= other;
        return result;
    }

    // vectorial multiplication never yields another vector
    template<typename ovt>
    Vec3<value_type> operator*(const Vec3<ovt>& other) const = delete;

    // scalar multiplication
    template<typename ovt>
    Vec3<value_type> operator*(const ovt& other) const {
        Vec3<value_type> result = *this;
        result *= other;
        return result;
    }

    // vectorial division does not exist
    template<typename ovt>
    Vec3<value_type> operator/(const Vec3<ovt>& other) const = delete;

    // scalar division
    template<typename ovt>
    Vec3<value_type> operator/(const ovt& other) const {
        Vec3<value_type> result = *this;
        result /= other;
        return result;
    }

    // dot product
    template<typename ovt>
    friend value_type operator*(const Vec3<value_type>& v1, const Vec3<ovt>& v2) {
        return static_cast<value_type>(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
    }


    /// Utility ///

    template<typename other_value_type>
    value_type sq_distance_to(const Vec3<other_value_type>& other) const {
        return static_cast<value_type>(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2));
    }

    value_type sq_magnitude() {
        return static_cast<value_type>(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
    }

    Vec3<value_type> normalized() {
        value_type mag = std::sqrt(sq_magnitude());
        return (*this) / mag;
    }

    /// Data ///

    value_type x = 0;
    value_type y = 0;
    value_type z = 0;

};


#endif //ELECTRICFIELD_POINT_H
