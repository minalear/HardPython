#ifndef MINALEAR_TEXTURE_H
#define MINALEAR_TEXTURE_H

#include <cstdint>

namespace minalear {
  class Texture2D {
    uint32_t id;
    int _width, _height, _nBits;
    
    public:
      Texture2D(const char *path);
      
      int width();
      int height();
      void bind();
  };
}

#endif