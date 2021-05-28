#include "glad/glad.h"
#include "sprite_batch.h"
#include "texture.h"
#include "glm/glm.hpp"
#include "shaders.h"
#include "glm/gtc/matrix_transform.hpp"

minalear::SpriteBatch::SpriteBatch(const int viewport_width, const int viewport_height)
  : shader(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE) {
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

  // matrix setup
  glm::mat4 proj, view, model;
  proj = glm::ortho(0.f, float(viewport_width), float(viewport_height), 0.f, -1.f, 1.f);
  view = glm::mat4(1.f);
  model = glm::mat4(1.f);

  shader.use();
  shader.set_uniform("proj", proj);
  shader.set_uniform("view", view);
  shader.set_uniform("model", model);
}

// Drawing
void minalear::SpriteBatch::_draw(Texture2D &texture, glm::mat4 model) {
  shader.use();
  shader.set_uniform("model", model);

  // TODO: Implement batching and deferred rendering
  texture.bind();
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void minalear::SpriteBatch::draw(Texture2D &texture, glm::mat4 model) {
  _draw(texture, model);
}
void minalear::SpriteBatch::draw(Texture2D &texture, glm::vec2 pos) {
  glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(pos, 0.f));
  model = glm::scale(model, glm::vec3(texture.width(), texture.height(), 1.f));

  _draw(texture, model);
}
void minalear::SpriteBatch::draw(Texture2D &texture, glm::vec2 pos, glm::vec2 scale) {
  glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(pos, 0.f));
  model = glm::scale(model, glm::vec3(texture.width(), texture.height(), 1.f) * glm::vec3(scale, 1.f));

  _draw(texture, model);
}