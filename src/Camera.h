//
// Created by Lars on 20/04/2019.
//

#ifndef INC_3DFIELDIMAGING_CAMERA_H
#define INC_3DFIELDIMAGING_CAMERA_H

#include "Vec3.h"

template<typename value_type>
struct Vec3;

struct Camera {

public:

    Camera(Vec3<> pos, Vec3<> tar, std::size_t width = 3840, std::size_t height = 2160, double mFOV = M_PI / 2.0) :
    position(pos), target(tar), image_width(width), image_height(height), FOV(mFOV) {}


    bool is_in_view(Vec3<> vec);
    Vec3<> convergence_point();
    Vec3<> directional_vector();
    double get_horizontal_fov();

    // center position of the image
    Vec3<> position;
    // the point the camera is looking at
    Vec3<> target;

    std::size_t image_width = 3840;
    std::size_t image_height = 2160;

    // vertical FOV, in radians (must be below pi, or 180°)
    double FOV = M_PI / 2.0;

};


#endif //INC_3DFIELDIMAGING_CAMERA_H
