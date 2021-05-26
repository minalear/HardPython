#include <cstdio>

#include "glad/glad.h"
#include "core/window.h"
#include "core/shader_program.h"
#include "core/shaders.h"
#include "core/sprite_batch.h"
#include "core/texture.h"
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

  auto sprite_batch = minalear::SpriteBatch();
  auto texture = minalear::Texture2D("content/textures/placeholder.png"); 

  // shader program setup
  auto shader = minalear::ShaderProgram(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
  shader.use();

  glm::mat4 proj, view, model;
  proj = glm::ortho(0.f, 800.f, 480.f, 0.f, -1.f, 1.f);
  view = glm::mat4(1.f);
  model = glm::mat4(1.f);
  model = glm::scale(model, glm::vec3(texture.width(), texture.height(), 1.f));

  shader.set_uniform("proj", proj);
  shader.set_uniform("view", view);
  shader.set_uniform("model", model);

  SDL_Event window_event;
  while (true) {
    if (SDL_PollEvent(&window_event)) {
      if (window_event.type == SDL_QUIT) break;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    sprite_batch.draw(texture, glm::vec2(0.f, 0.f));

    game_window.dt();
    game_window.swap_buffers();
  }

  return 0;
}