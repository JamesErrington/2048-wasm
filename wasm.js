'use strict'

const canvas = document.getElementById('app-canvas');
const ctx = canvas.getContext('2d');

function color_hex(color) {
	  const r = ((color>>(0*8))&0xFF).toString(16).padStart(2, '0');
	  const g = ((color>>(1*8))&0xFF).toString(16).padStart(2, '0');
	  const b = ((color>>(2*8))&0xFF).toString(16).padStart(2, '0');
	  const a = ((color>>(3*8))&0xFF).toString(16).padStart(2, '0');
	  return "#"+r+g+b+a;
}

function platform_fill_rect(x, y, w, h, c) {
		ctx.fillStyle = color_hex(c);
		ctx.fillRect(x, y, w, h);
}

WebAssembly
		.instantiateStreaming(fetch('build/main.wasm'), {
				env: {
						platform_fill_rect,
				}
		})
		.then(wasm => {
				wasm.instance.exports.init();
		});
