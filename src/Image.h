//
// Created by Lars on 15/04/2019.
//

#ifndef ELECTRICFIELD_IMAGE_H
#define ELECTRICFIELD_IMAGE_H

#include "Color.h"
#include "lodepng.h"

#include <vector> // container type
#include <stdexcept> // runtime_error
#include <string> // filenames etc.

class Image {
public:

    typedef typename std::vector<Color>                         container_type;
    typedef typename container_type::iterator                   iterator;
    typedef typename container_type::const_iterator             const_iterator;
    typedef typename container_type::reverse_iterator           reverse_iterator;
    typedef typename container_type::const_reverse_iterator     const_reverse_iterator;

    /**
     * \brief Initialize a white (or differently colored) image of specified dimensions.
     */
    explicit Image(std::size_t mWidth, std::size_t mHeight, Color background = Color(255, 255, 255, 255)) : colordata(mWidth * mHeight, background), w(mWidth), h(mHeight) {}

    /**
     * \brief Open an image from a file.
     */
    explicit Image(const std::string& filename) : colordata() {
        std::vector<unsigned char> rawdata;
        unsigned width, height;

        unsigned error = lodepng::decode(rawdata, width, height, filename);

        if (error) {
            throw std::runtime_error("Decoder Error " + std::to_string(error) + ": " + lodepng_error_text(error));
        }

        w = width;
        h = height;
        colordata.reserve(w * h);
        for (std::size_t i = 0; i < rawdata.size(); i += 4) {
            Color currentColor(rawdata.at(i), rawdata.at(i + 1), rawdata.at(i + 2), rawdata.at(i + 3));
            colordata.emplace_back(currentColor);
        }
    }

    /// Iterators ///

    iterator begin() {
        return colordata.begin();
    }

    const_iterator cbegin() {
        return colordata.cbegin();
    }

    reverse_iterator rbegin() {
        return colordata.rbegin();
    }

    const_reverse_iterator crbegin() {
        return colordata.crbegin();
    }

    iterator end() {
        return colordata.end();
    }

    const_iterator cend() {
        return colordata.cend();
    }

    reverse_iterator rend() {
        return colordata.rend();
    }

    const_reverse_iterator crend() {
        return colordata.crend();
    }

    /// Member Access ///

    Color get_pixel(std::size_t x, std::size_t y) const {
        return colordata.at(w * y + x);
    }

    void set_pixel(std::size_t x, std::size_t y, Color value) {
        colordata.at(w * y + x) = value;
    }

    std::size_t width() { return w; }
    std::size_t height() { return h; }

    std::vector<Color> get_color_data() const {
        return colordata;
    }

    /**
     * \brief Returns the raw RGBA-ordered vector of individual channel values
     */
    std::vector<unsigned char> get_raw_data() const {
        std::vector<unsigned char> result;
        result.reserve(4 * w * h);

        for (const Color c : colordata) {
            result.emplace_back(c.R);
            result.emplace_back(c.G);
            result.emplace_back(c.B);
            result.emplace_back(c.A);
        }

        return result;
    }

    /// Utility ///

    void save_to_file(const std::string& filename) {
        unsigned error = lodepng::encode(filename, get_raw_data(), w, h);

        if (error) {
            throw std::runtime_error("Encoder Error " + std::to_string(error) + ": " + lodepng_error_text(error));
        }
    }

    /**
     * \brief Clear the image with a single color
     */
    void clear(Color clearcolor = {255, 255, 255, 255}) {
        for (Color& c : colordata) {
            c = clearcolor;
        }
    }

private:
    std::vector<Color> colordata;
    std::size_t w = 0, h = 0;

};


#endif //ELECTRICFIELD_IMAGE_H
