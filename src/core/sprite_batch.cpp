#include "glad/glad.h"
#include "sprite_batch.h"
#include "texture.h"
#include "glm/glm.hpp"

minalear::SpriteBatch::SpriteBatch() {
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  float buffer[] = {
    // POS      UV          COLOR
    0.f, 0.f,   0.f, 0.f,   1.f, 1.f, 1.f,
    0.f, 1.f,   0.f, 1.f,   1.f, 1.f, 1.f,
    1.f, 0.f,   1.f, 0.f,   1.f, 1.f, 1.f,
    1.f, 0.f,   1.f, 0.f,   1.f, 1.f, 1.f,
    0.f, 1.f,   0.f, 1.f,   1.f, 1.f, 1.f,
    1.f, 1.f,   1.f, 1.f,   1.f, 1.f, 1.f
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0); // pos
  glEnableVertexAttribArray(1); // uv
  glEnableVertexAttribArray(2); // color

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (GLvoid*)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (GLvoid*)(2 * sizeof(float)));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (GLvoid*)(4 * sizeof(float)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void minalear::SpriteBatch::draw(Texture2D &texture, glm::vec2 pos) {
  // TODO: Implement actual batching
  texture.bind();
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 6); // two triangles make a quad
  glBindVertexArray(0);
}