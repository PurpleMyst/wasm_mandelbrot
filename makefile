.PHONY: all
all: index.html index.js index.css

.PHONY: run
run: all
	${BROWSER} index.html

.PHONY: clean
clean:
	rm -f index.js index.wasm

index.js: mandelbrot.c pre.js
	emcc \
		-O3 \
		--pre-js pre.js \
		-s "EXPORTED_FUNCTIONS=['_draw_mandelbrot', '_malloc', '_free']" \
		-s "EXTRA_EXPORTED_RUNTIME_METHODS=['cwrap']" \
		mandelbrot.c -o index.js
