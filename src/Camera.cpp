//
// Created by Lars on 20/04/2019.
//

#include "Camera.h"
#include <iostream>

#include <cmath> // tan
#include "math.h" // deg_to_rad

namespace {
    double get_phi(Vec3<> pos) {
        if (pos.x > 0) {
            return atan(pos.y / pos.x);
        } else if (pos.x == 0) {
            return pos.y >= 0 ? M_PI / 2.0 : -M_PI / 2.0;
        } else {
            if (pos.y >= 0) {
                return atan(pos.y / pos.x) + M_PI;
            } else {
                return atan(pos.y / pos.x) - M_PI;
            }
        }
    }
}

bool Camera::is_in_view(Vec3<> vec) {
    // Coordinate transform the origin to the convergence point of the camera
    // and then check if the spherical coordinates work out
    Vec3<> tr_origin = convergence_point();
    Vec3<> tr_pos = position - tr_origin;
    Vec3<> tr_vec = vec - tr_origin;

    // the transformed camera always looks away from the origin (convergence point)
    // so we only check for radius and minimum and maximum angle values
    double sq_cam_radius = tr_pos.sq_magnitude();
    double sq_vec_radius = tr_vec.sq_magnitude();
    if (sq_vec_radius < sq_cam_radius) { return false; }

    // angles are in radians.
    double horizontal_fov = get_horizontal_fov();
    // theta = arccos(z / r)
    // theta is in [0, pi]
    double cam_theta = acos(tr_pos.z / sqrt(sq_cam_radius));
    double vec_theta = acos(tr_vec.z / sqrt(sq_vec_radius));
    double min_theta = cam_theta - horizontal_fov / 2.0;
    double max_theta = cam_theta + horizontal_fov / 2.0;

    if (vec_theta < min_theta || vec_theta > max_theta) { return false; }

    // phi is in [-pi, pi]
    double cam_phi = get_phi(tr_pos);
    double vec_phi = get_phi(tr_vec);
    double min_phi = cam_phi - FOV / 2.0;
    double max_phi = cam_phi + FOV / 2.0;

    if (min_phi < 0) { min_phi += 2 * M_PI; }
    if (max_phi > 2 * M_PI) { max_phi -= 2 * M_PI; }

    if (min_phi < max_phi) {
        return vec_phi >= min_phi && vec_phi <= max_phi;
    } else {
        return vec_phi <= min_phi && vec_phi >= max_phi;
    }
}

Vec3<> Camera::convergence_point() {
    // the height of a right pyramid behind the camera (with the convergence point as the peak)
    // is given by h = h_i / (2 * tan(alpha / 2))
    // where h_i is the image_height of the camera and alpha is the vertical fov
    // the convergence point is thus given by the position minus the directional vector with magnitude h
    double h = image_height / (2 * tan(FOV / 2.0));
    return position - (directional_vector() * h);
}

Vec3<> Camera::directional_vector() {
    return (target - position).normalized();
}

double Camera::get_horizontal_fov() {
    return 2 * atan((static_cast<double>(image_width) / image_height) * tan(FOV / 2.0));
}
