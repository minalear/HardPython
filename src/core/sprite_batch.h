#ifndef MINALEAR_SPRITE_BATCH_H
#define MINALEAR_SPRITE_BATCH_H

#include <cstdint>
#include "texture.h"
#include "shader_program.h"
#include "glm/glm.hpp"

namespace minalear {
  class SpriteBatch {
    uint32_t vao, vbo;
    //ShaderProgram shader;

    public:
      SpriteBatch();
      // TODO: Add destructor
      void draw(Texture2D &texture, glm::vec2 pos);
  };
}

#endif