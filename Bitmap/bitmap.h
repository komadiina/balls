#ifndef BITMAP_H
#define BITMAP_H

#include <string>
#include <vector>
#include <cstdint>
#include <format>

// ----------------------------------------------------------------------------
/**
 * Represents a single Pixel in the image. A Pixel has red, green, and blue
 * components that are mixed to form a color. Each of these values can range
 * from 0 to 255
 **/
class Pixel
{
public:
    // Stores the individual color components.
    int red, green, blue;

    // Initializes a Pixel with a default black color.
    Pixel() : red(0), green(0), blue(0) {}

    // Initializes a color Pixel with the specified RGB values.
    Pixel(int r, int g, int b) : red(r), green(g), blue(b) {}

    friend Pixel operator*(const Pixel &p, float scalar)
    {
        return Pixel(
            (float)p.red * scalar,
            (float)p.green * scalar,
            (float)p.blue * scalar);
    }

    friend Pixel operator*(const Pixel &a, const Pixel &b)
    {
        return Pixel(
            (expand(normalize(a.red) * normalize(b.red))),
            (expand(normalize(a.blue) * normalize(b.blue))),
            (expand(normalize(a.green) * normalize(b.green))));
    }

    friend Pixel operator-(const Pixel &a, const Pixel &b)
    {
        return Pixel(
            clamp(a.red - b.red),
            clamp(a.green - b.green),
            clamp(a.blue - b.blue));
    }

    friend Pixel operator+(const Pixel &a, const Pixel &b)
    {
        return Pixel(
            clamp(a.red + b.red),
            clamp(a.green + b.green),
            clamp(a.blue + b.blue));
    }

    friend bool operator==(const Pixel &a, const Pixel &b)
    {
        return a.red == b.red && a.green == b.green & a.blue == b.blue;
    }

    friend bool operator!=(const Pixel &a, const Pixel &b)
    {
        return !(a == b);
    }

    friend std::ostream &operator<<(std::ostream &os, const Pixel &obj)
    {
        return os << std::format("({}, {}, {})", obj.red, obj.green, obj.blue);
    }

private:
    static float normalize(int value, int min = 0, int max = 255)
    {
        return (float)(value - min) / (float)(max - min);
    }

    static int clamp(int value, int min = 0, int max = 255)
    {
        return std::max(min, std::min(max, value));
    }

    static int expand(float normalized, int limit = 255)
    {
        return normalized * limit;
    }
};

// ----------------------------------------------------------------------------
// To abbreviate a pixel matrix built as a vector of vectors
typedef std::vector<std::vector<Pixel>> PixelMatrix;

// ----------------------------------------------------------------------------
/**
 * Represents a bitmap where a grid of pixels (in row-major order)
 * describes the color of each pixel within the image. Limited to Windows BMP
 * formatted images with no compression and 24 bit color depth.
 **/
class Bitmap
{
private:
    PixelMatrix pixels;

public:
    /**
     * Opens a file as its name is provided and reads pixel-by-pixel the colors
     * into a matrix of RGB pixels. Any errors will cout but will result in an
     * empty matrix (with no rows and no columns).
     *
     * @param name of the filename to be opened and read as a matrix of pixels
     **/
    void open(std::string);

    /**
     * Saves the current image, represented by the matrix of pixels, as a
     * Windows BMP file with the name provided by the parameter. File extension
     * is not forced but should be .bmp. Any errors will cout and will NOT
     * attempt to save the file.
     *
     * @param name of the filename to be written as a bmp image
     **/
    void save(std::string);

    /**
     * Validates whether or not the current matrix of pixels represents a
     * proper image with non-zero-size rows and consistent non-zero-size
     * columns for each row. In addition, each pixel in the matrix is validated
     * to have red, green, and blue components with values between 0 and 255
     *
     * @return boolean value of whether or not the matrix is a valid image
     **/
    bool isImage();

    /**
     * Provides a vector of vector of pixels representing the bitmap
     *
     * @return the bitmap image, represented by a matrix of RGB pixels
     **/
    PixelMatrix toPixelMatrix();

    /**
     * Overwrites the current bitmap with that represented by a matrix of
     * pixels. Does not validate that the new matrix of pixels is a proper
     * image.
     *
     * @param a matrix of pixels to represent a bitmap
     **/
    void fromPixelMatrix(const PixelMatrix &);
};

#endif
