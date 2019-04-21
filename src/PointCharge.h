//
// Created by Lars on 21/04/2019.
//

#ifndef INC_3DFIELDIMAGING_POINTCHARGE_H
#define INC_3DFIELDIMAGING_POINTCHARGE_H

#include "Vec3.h"
#include "VectorSpace.h"

class ElectricField;

struct PointCharge {

    PointCharge() = default;
    PointCharge(double c, Vec3<> vec) : charge(c), position(vec) {}

    double charge = 0;
    Vec3<> position = {0, 0, 0};


    Vec3<> get_field_at(Vec3<> pos) const;
    double get_field_value_at(Vec3<> pos) const;

    double get_relevant_sq_radius(double minfieldstrength = 1.0 / 255) const;

    VectorSpace get_relevant_field(double minfieldstrength = 1.0 / 255) const;

};


#endif //INC_3DFIELDIMAGING_POINTCHARGE_H
