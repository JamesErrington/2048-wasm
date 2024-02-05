SRC_FILE := main
BUILD_DIR := build
CFLAGS := -Wall -Wextra -O3 -nostdlib -fno-builtin
LFLAGS := -flto -Wl,--export=init -Wl,--export=handle_key -Wl,--export=render -Wl,--no-entry -Wl,--lto-O3 -Wl,--allow-undefined

compile: main.c
	mkdir -p ${BUILD_DIR}
	clang ${CFLAGS} ${LFLAGS} --target=wasm32 -o ${BUILD_DIR}/${SRC_FILE}.wasm ${SRC_FILE}.c

serve:
	python3 -m http.server 8080

clean:
	rm -rf ${BUILD_DIR}

.PHONY: clean serve
