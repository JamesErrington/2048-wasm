'use strict'

let wasm;
const canvas = document.getElementById('app-canvas');
const ctx = canvas.getContext('2d');

function cstrlen(mem, ptr) {
    let len = 0;
    while (mem[ptr] != 0) {
        len++;
        ptr++;
    }
    return len;
}

function cstr_by_ptr(mem_buffer, ptr) {
    const mem = new Uint8Array(mem_buffer);
    const len = cstrlen(mem, ptr);
    const bytes = new Uint8Array(mem_buffer, ptr, len);
    return new TextDecoder().decode(bytes);
}

function color_hex(color) {
	  const r = ((color>>(0*8))&0xFF).toString(16).padStart(2, '0');
	  const g = ((color>>(1*8))&0xFF).toString(16).padStart(2, '0');
	  const b = ((color>>(2*8))&0xFF).toString(16).padStart(2, '0');
	  const a = ((color>>(3*8))&0xFF).toString(16).padStart(2, '0');
	  return "#"+r+g+b+a;
}

function keycode(key) {
	switch (key) {
		case 'ArrowLeft':
		case 'a':
			return 37;
		case 'ArrowUp':
		case 'w':
			return 38;
		case 'ArrowRight':
		case 'd':
			return 39;
		case 'ArrowDown':
		case 's':
			return 40;
		default:
			return 0;
	}
}

function platform_fill_rect(x, y, width, height, color) {
		ctx.fillStyle = color_hex(color);
		ctx.fillRect(x, y, width, height);
}

function platform_fill_text(x, y, text_ptr, size, color) {
	const buffer = wasm.instance.exports.memory.buffer;
	const text = cstr_by_ptr(buffer, text_ptr);

	ctx.font = size+"px sans-serif";
	ctx.fillStyle = color_hex(color);
	ctx.textAlign = "center";
	ctx.textBaseline = "middle";
	ctx.fillText(text, x, y);
}

function platform_log(text_ptr) {
	const buffer = wasm.instance.exports.memory.buffer;
	const text = cstr_by_ptr(buffer, text_ptr);

	console.log(text);
}

WebAssembly
		.instantiateStreaming(fetch('build/game.wasm'), {
				env: {
						platform_fill_rect,
						platform_fill_text,
						platform_log,
				}
		})
		.then(w => {
				wasm = w;

				document.addEventListener('keyup', event => {
					const result = wasm.instance.exports.handle_key(keycode(event.key));
					if (result > 0) {
						setTimeout(() => {
							alert("You won!");
							wasm.instance.exports.init(Date.now());
						}, 0)
					}
				})

				wasm.instance.exports.init(Date.now());
		});
