//
// Created by Lars on 20/04/2019.
//

#ifndef INC_3DFIELDIMAGING_MATH_H
#define INC_3DFIELDIMAGING_MATH_H

#include <cmath>

struct math {

    static double rad_to_deg(double rad) {
        return 180.0 * rad / M_PI;
    }

    static double deg_to_rad(double deg) {
        return M_PI * deg / 180.0;
    }
};

#endif //INC_3DFIELDIMAGING_MATH_H
