#include <node.h>

using namespace v8;

void runMandelbrot(unsigned char* array, int width, int height, double pixel_size, double x0, double y0) {
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      double cr = x0 + pixel_size * i;
      double ci = y0 + pixel_size * j;
      double zr = 0.0f;
      double zi = 0.0f;
      double zrzi, zr2, zi2;
      int k;
      for(k = 0; k < 256; k++) {
          zrzi = zr * zi;
          zr2 = zr * zr;
          zi2 = zi * zi;
          zr = zr2 - zi2 + cr;
          zi = zrzi + zrzi + ci;
          if(zi2 + zr2 >= 2.0) {
              break;
          }
      }
      if(k > 255){
          k = 255;
      }

      int index = j * width + i;
      array[4 * index] = array[4 * index + 1] = array[4 * index + 2] = 255 - k;
      array[4 * index + 3] = 255;
    }
  }
}


void Method(const FunctionCallbackInfo<Value>& args) {
  Local<Uint8ClampedArray> array = args[0].As<Uint8ClampedArray>();
  unsigned char* ptr = (unsigned char*)array->Buffer()->GetContents().Data();
  runMandelbrot(ptr, 300, 200, 0.01, -2.0, -1.0);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "mandelbrot", Method);
}

NODE_MODULE(addon, init)
