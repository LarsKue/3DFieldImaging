//
// Created by Lars on 19/04/2019.
//

#include <iostream>
#include "lodepng.h"
#include "Vec3.h"

#include "Image.h"

#include "Camera.h"


int main() {

    Camera c({0, 0, 0}, {3, 3, 3});

    std::cout << c.is_in_view({1, 1, 1});

    return 0;
}