#ifndef MINALEAR_TEXTURE_H
#define MINALEAR_TEXTURE_H

namespace minalear {
  class Texture2D {
    uint32_t id;
    int width, height, nBits;
    
    public:
      Texture2D(const char *path);
      
      int width();
      int height();
      void bind();
  };
}

#endif