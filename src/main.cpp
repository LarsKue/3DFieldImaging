//
// Created by Lars on 19/04/2019.
//

#include <iostream>
#include "lodepng.h"
#include "Point.h"

#include "Image.h"


int main() {

    Point p1(0.0, 3.0, 4.0);

    Point p2(0, 0, 0);

    std::cout << p1.sq_distance_to(p2) << std::endl;

    return 0;
}