//
// Created by Lars on 21/04/2019.
//

#ifndef INC_3DFIELDIMAGING_ELECTRICFIELD_H
#define INC_3DFIELDIMAGING_ELECTRICFIELD_H

#include <vector>

#include "Vec3.h"

#include "PointCharge.h"

#include "Camera.h"

#include "Image.h"

#include "VectorSpace.h"

/**
 * \brief Discretely Calculated Electric Field based on a number of Point Charges
 * May generate an image from this.
 */
class ElectricField {

public:

    ElectricField() = default;
    ElectricField(std::size_t x, std::size_t y, std::size_t z);

    void calculate(const std::vector<PointCharge>& charges);
    void calculate_approx(const std::vector<PointCharge>& charges, double minFieldVal);

    /**
     * \brief Generates and returns an Image that represents the field vectors at every point of the field.
     * Note: Wrapping the raw pointer is the user's responsibility. We allocate on the heap because images may
     * be very large (i.e. several Megabytes in size)
     * \param colorSelectionFunc A function that takes a field vector as a parameter and returns the
     * color to be used for that pixel.
     */
    template<typename func>
    Image* generate_image(const Camera& cam, func colorSelectionFunc, double fineness) {
        auto* result = new Image(cam.image_width, cam.image_height);
    }

    // origin needs to be discrete
    Vec3<long long> origin = {0, 0, 0};

    // dimensions
    std::size_t size_x = 0;
    std::size_t size_y = 0;
    std::size_t size_z = 0;

private:

    VectorSpace field_vectors = VectorSpace(0, 0, 0);

};


#endif //INC_3DFIELDIMAGING_ELECTRICFIELD_H
