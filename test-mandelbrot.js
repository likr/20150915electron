var mandelbrot = require('./mandelbrot');
var b = new Uint8Array(300 * 200 * 4);
mandelbrot.mandelbrot(b);
console.log(b);
