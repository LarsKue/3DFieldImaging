//
// Created by Lars on 15/04/2019.
//

#ifndef ELECTRICFIELD_COLOR_H
#define ELECTRICFIELD_COLOR_H

#include <iostream> // operator<<

struct Color {

    Color() = default;
    Color(unsigned char red, unsigned char green, unsigned char blue) : R(red), G(green), B(blue) {}
    Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) : R(red), G(green), B(blue), A(alpha) {}

    unsigned char R = 255;
    unsigned char G = 255;
    unsigned char B = 255;
    unsigned char A = 255;

    friend std::ostream& operator<<(std::ostream& stream, const Color& c) {
        stream << "Color[" << static_cast<int>(c.R) << "," << static_cast<int>(c.G) << "," << static_cast<int>(c.B) << "," << static_cast<int>(c.A) << "]";
        return stream;
    }

};


#endif //ELECTRICFIELD_COLOR_H
