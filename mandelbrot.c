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

#define LOW_R 0xE1
#define LOW_G 0xE1
#define LOW_B 0xE1

#define HIGH_R 0x00
#define HIGH_G 0x00
#define HIGH_B 0x00

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

            double fraction = ((double)iterations) / MAX_ITERATIONS;
            rgba_pixels[4 * (y * width + x) + 0] = (HIGH_R - LOW_R) * fraction + LOW_R; // R
            rgba_pixels[4 * (y * width + x) + 1] = (HIGH_G - LOW_G) * fraction + LOW_G; // G
            rgba_pixels[4 * (y * width + x) + 2] = (HIGH_B - LOW_B) * fraction + LOW_B; // B
            rgba_pixels[4 * (y * width + x) + 3] = 0xFF; // A
        }
    }
}
