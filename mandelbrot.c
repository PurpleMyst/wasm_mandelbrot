/* TODO: Extend this to do more than two colors. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <complex.h>

#define MAX_ITERATIONS 0xFF

#define REAL_START -2
#define REAL_END 1
#define IMAG_START -1
#define IMAG_END 1

void draw_mandelbrot(const size_t width, const size_t height, uint8_t *rgba_pixels) {
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            uint_fast8_t iterations = 0;
            double complex c = (REAL_START + (((double)x) / width) * (REAL_END - REAL_START)) +
                (IMAG_START + (((double)y) / height) * (IMAG_END - IMAG_START)) * I;

            for (double complex z = 0;
                    cabs(z) <= 2 && iterations < MAX_ITERATIONS;
                    z = z * z + c, ++iterations)
                ;

            if (iterations == MAX_ITERATIONS) {
                rgba_pixels[4 * (y * width + x) + 0] = 0xFF; // R
                rgba_pixels[4 * (y * width + x) + 1] = 0xFF; // G
                rgba_pixels[4 * (y * width + x) + 2] = 0xFF; // B
                rgba_pixels[4 * (y * width + x) + 3] = 0xFF; // A
            } else {
                rgba_pixels[4 * (y * width + x) + 0] = 0x00; // R
                rgba_pixels[4 * (y * width + x) + 1] = 0x00; // G
                rgba_pixels[4 * (y * width + x) + 2] = 0x00; // B
                rgba_pixels[4 * (y * width + x) + 3] = 0xFF; // A
            }
        }
    }
}
