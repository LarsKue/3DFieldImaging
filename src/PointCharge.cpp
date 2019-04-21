//
// Created by Lars on 21/04/2019.
//

#include "PointCharge.h"

/**
 * \brief Returns the field vector at point pos.
 */
Vec3<> PointCharge::get_field_at(Vec3<> pos) const {
    double field_value = get_field_value_at(pos);
    return field_value * (pos - position).normalized();
}


/**
 * \brief Returns the field value the charge generates at the point pos, scaled to a factor of 1/(4*pi*epsilon_0)
 * E ~ q / r^2
 * E = 1 / (4 * pi * epsilon_0) * q / r^2
 */
double PointCharge::get_field_value_at(Vec3<> pos) const {
    double distance = pos.sq_distance_to(position);

    if (distance == 0) { return std::numeric_limits<double>::max(); }

    return charge / distance;
}

double PointCharge::get_relevant_sq_radius(double minfieldstrength) const {
    if (minfieldstrength == 0) {
        return std::numeric_limits<double>::max();
    }
    // q / r^2 = minfieldstrength
    // -> r^2 = q / minfieldstrength
    return fabs(charge / minfieldstrength);
}

VectorSpace PointCharge::get_relevant_field(double minfieldstrength) const {
    auto radius = static_cast<std::size_t>(std::round(sqrt(get_relevant_sq_radius(minfieldstrength))));
    Vec3<long long> origin = Vec3<long long>(-radius, -radius, -radius) + position;

}
