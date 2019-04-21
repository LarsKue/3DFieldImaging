//
// Created by Lars on 21/04/2019.
//

#include "VectorSpace.h"

#include <algorithm>
#include <functional>

VectorSpace VectorSpace::operator-() const {
    VectorSpace result(*this);
    for (auto& x_vec : result) {
        for (auto& y_vec : x_vec) {
            std::transform(y_vec.begin(), y_vec.end(), y_vec.begin(), std::negate<>());
        }
    }
    return result;
}

VectorSpace& VectorSpace::operator+=(const VectorSpace& other) {
    Vec3<long long> transform_vec = other.origin - origin;
    for (std::size_t x = 0; x < other.x_size(); ++x) {
        if (x + transform_vec.x < 0) { continue; }
        if (x + transform_vec.x > x_size()) { break; }
        for (std::size_t y = 0; y < other.y_size(); ++y) {
            if (y + transform_vec.y < 0) { continue; }
            if (y + transform_vec.y > y_size()) { break; }
            for (std::size_t z = 0; z < other.z_size(); ++z) {
                if (z + transform_vec.z < 0) { continue; }
                if (z + transform_vec.z > z_size()) { break; }
                this->at_coords(Vec3(x, y, z) + transform_vec) += other.at_coords(Vec3(x, y, z));
            }
        }
    }
    return *this;
}

VectorSpace& VectorSpace::operator-=(const VectorSpace& other) {
    return *this += -other;
}

Vec3<> VectorSpace::at_coords(const Vec3<std::size_t>& coords) const {
    return at(coords.x).at(coords.y).at(coords.z);
}

Vec3<>& VectorSpace::at_coords(const Vec3<std::size_t>& coords) {
    return at(coords.x).at(coords.y).at(coords.z);
}

void VectorSpace::reset(Vec3<> value) {
    for (auto& x_vec : *this) {
        for (auto& y_vec : x_vec) {
            for (auto& item : y_vec) {
                item = value;
            }
        }
    }
}
