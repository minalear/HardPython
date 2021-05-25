#include <cstdio>

#include "glad/glad.h"
#include "core/window.h"
#include "core/shader_program.h"
#include "core/shaders.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(int argc, char* argv[]) {
  auto game_window = minalear::GameWindow("Hard Python", 800, 480);

  // setup blend/clear color
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glViewport(0, 0, game_window.width(), game_window.height());

  // shader program setup
  auto shader = minalear::ShaderProgram(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
  shader.use();

  glm::mat4 proj, view, model;
  proj = glm::ortho(0.f, 800.f, 480.f, 0.f, -1.f, 1.f);
  view = glm::mat4(1.f);
  model = glm::mat4(1.f);

  shader.set_uniform("proj", proj);
  shader.set_uniform("view", view);
  shader.set_uniform("model", model);

  // temp vao/vbo values
  GLuint vao, vbo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  float buffer[] = {
    400.f, 120.f, 1.0f, 1.0f, 0.0f,
    600.f, 360.f, 0.0f, 1.0f, 1.0f,
    200.f, 360.f, 1.0f, 0.0f, 1.0f
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0); // pos
  glEnableVertexAttribArray(1); // color

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  SDL_Event window_event;
  while (true) {
    if (SDL_PollEvent(&window_event)) {
      if (window_event.type == SDL_QUIT) break;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    game_window.dt();
    game_window.swap_buffers();
  }

  return 0;
}