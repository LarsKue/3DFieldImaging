//
// Created by Lars on 21/04/2019.
//

#include "ElectricField.h"

ElectricField::ElectricField(std::size_t x, std::size_t y, std::size_t z) : size_x(x), size_y(y), size_z(z) {}


/**
 * \brief Calculate the exact electric field at discrete points in space
 */
void ElectricField::calculate(const std::vector<PointCharge>& charges) {
    field_vectors.reset();
    for (const auto& c : charges) {
        // initialize vector space to zero
        VectorSpace current(size_x, size_y, size_z, origin);

        for (std::size_t x = 0; x < size_x; ++x) {
            for (std::size_t y = 0; y < size_y; ++y) {
                for (std::size_t z = 0; z < size_z; ++z) {
                    current.at_coords({x, y, z}) = c.get_field_at(Vec3<>(x, y, z) - origin);
                }
            }
        }

        field_vectors += current;
    }

}


void ElectricField::calculate_approx(const std::vector<PointCharge>& charges, double minFieldVal) {
    // Consider increasing the field strength by a flat amount across the board based on total charge in the field
    field_vectors = VectorSpace(size_x, size_y, size_z, {0, 0, 0});
    /// add field in cube around pointcharges up to relevant radius
    for (const auto& c : charges) {
        field_vectors += c.get_relevant_field(minFieldVal);
    }
}