//
// Created by Lars on 21/04/2019.
//

#ifndef INC_3DFIELDIMAGING_VECTORSPACE_H
#define INC_3DFIELDIMAGING_VECTORSPACE_H

#include <vector>
#include "Vec3.h"

class VectorSpace : public std::vector<std::vector<std::vector<Vec3<>>>> {

public:

    explicit VectorSpace(Vec3<long long> orig) : origin(orig) {}
    VectorSpace(std::size_t x, std::size_t y, std::size_t z, Vec3<long long> orig = {0, 0, 0}) : std::vector<std::vector<std::vector<Vec3<>>>>(x, std::vector<std::vector<Vec3<>>>(y, std::vector<Vec3<>>(z, {0, 0, 0}))), origin(orig) {
        // this just zero-initializes the VectorSpace of specified dimensions.
    }

    /**
     * \brief Initializes the VectorSpace with Values from a Function for each Point
     * \param gen A Function that must take a Vec3<std::size_t> as a parameter and output the desired field
     * vector as a Vec3<>
     */
    template<typename Generator>
    VectorSpace(std::size_t x, std::size_t y, std::size_t z, Vec3<long long> orig, Generator gen) : std::vector<std::vector<std::vector<Vec3<>>>>(x, std::vector<std::vector<Vec3<>>>(y, std::vector<Vec3<>>(z, {0, 0, 0}))), origin(orig) {
        for (std::size_t mX = 0; mX < x; ++mX) {
            for (std::size_t mY = 0; mY < y; ++mY) {
                for (std::size_t mZ = 0; mZ < z; ++mZ) {
                    at_coords({mX, mY, mZ}) = gen({mX, mY, mZ});
                }
            }
        }
    }

    // origin has to be discreet, otherwise adding etc. would not work
    Vec3<long long> origin = {0, 0, 0};

    VectorSpace operator-() const;

    VectorSpace& operator+=(const VectorSpace& other);
    VectorSpace& operator-=(const VectorSpace& other);

    Vec3<> at_coords(const Vec3<std::size_t>& coords) const;
    Vec3<>& at_coords(const Vec3<std::size_t>& coords);

    std::size_t x_size() const { return size(); }
    std::size_t y_size() const { return at(0).size(); }
    std::size_t z_size() const { return at(0).at(0).size(); }

    void reset(Vec3<> value = {0, 0, 0});

};


#endif //INC_3DFIELDIMAGING_VECTORSPACE_H
