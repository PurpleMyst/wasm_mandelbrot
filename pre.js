/* jshint browser: true, devel: true, undef: true, typed: true */
/* global ImageData, Module */

Module.onRuntimeInitialized = function() {
    "use strict";

    var draw_mandelbrot = Module.cwrap("draw_mandelbrot", "void", ["size_t", "size_t", "[uint8_t]"]);

    var canvas = document.createElement("canvas");
    var ctx = canvas.getContext("2d");
    document.body.appendChild(canvas);

    function allocate_uint8_array(buffer_size) {
        var buffer_offset = Module._malloc(buffer_size);

        var zeroed_buffer = new Uint8ClampedArray(buffer_size);
        Module.HEAPU8.set(zeroed_buffer, buffer_offset);

        return {
            data: Module.HEAPU8.subarray(buffer_offset, buffer_offset  + buffer_size),
            offset: buffer_offset,
        };
    }

    function draw() {
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
        var rgba_pixels = allocate_uint8_array(canvas.width * canvas.height * 4);
        console.time("drawing mandelbrot");
        draw_mandelbrot(canvas.width, canvas.height, rgba_pixels.offset);
        console.timeEnd("drawing mandelbrot");

        ctx.putImageData(new ImageData(new Uint8ClampedArray(rgba_pixels.data), canvas.width, canvas.height), 0, 0);

        Module._free(rgba_pixels.offset);
    }

    draw();
};
