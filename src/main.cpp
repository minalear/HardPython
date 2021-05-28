#include <cstdio>
#include <cstdarg>

#include "glad/glad.h"
#include "core/window.h"
#include "core/sprite_batch.h"
#include "core/texture.h"
#include "core/logger.h"
#include "core/input.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// standard logger for program
void fmt_logger(const char* msg, va_list args) {
  vprintf(msg, args);
  putchar('\n');
}

int main(int argc, char* argv[]) {
  minalear::set_default_logger(fmt_logger);
 
  const int viewport_width = 1280;
  const int viewport_height = 720;
  auto game_window = minalear::GameWindow("Hard Python", viewport_width, viewport_height);
  minalear::init_input();

  // setup blend/clear color
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.f, 0.f, 0.f, 1.f);
  //glViewport(0, 0, game_window.width(), game_window.height());
  //glViewport(0, 0, viewport_width, viewport_height);

  auto sprite_batch = minalear::SpriteBatch(viewport_width, viewport_height);
  auto texture = minalear::Texture2D("content/textures/placeholder.png");

  float dt = game_window.dt();
  const float update_step = 0.01667f;

  glm::vec2 entity_pos = glm::vec2(0.f, 0.f);
  //glm::mat4 model = glm::scale(glm::mat4(1.f), glm::vec3(viewport_width, viewport_height, 1.f));
  glm::mat4 model = glm::scale(glm::mat4(1.f), glm::vec3(512.f, 512.f, 1.f));

  SDL_Event window_event;
  while (true) {
    // handle input
    minalear::handle_input();
    if (SDL_PollEvent(&window_event)) {
      if (window_event.type == SDL_QUIT) break;
      if (minalear::key_down(SDL_SCANCODE_ESCAPE)) break;
    }

    // update logic
    dt += game_window.dt();
    if (dt >= update_step) {
      dt -= update_step;
      // minalear::log("update step: %f", dt);

      const float speed = 250.f;
      if (minalear::key_down(SDL_SCANCODE_W)) {
        entity_pos.y -= speed * update_step;
      }
      if (minalear::key_down(SDL_SCANCODE_S)) {
        entity_pos.y += speed * update_step;
      }
      if (minalear::key_down(SDL_SCANCODE_A)) {
        entity_pos.x -= speed * update_step;
      }
      if (minalear::key_down(SDL_SCANCODE_D)) {
        entity_pos.x += speed * update_step;
      }

      if (minalear::key_down(SDL_SCANCODE_SPACE)) {
        minalear::log("pos: %fx%f", entity_pos.x, entity_pos.y);
      }
    }

    // rendering logic
    glClear(GL_COLOR_BUFFER_BIT);
    sprite_batch.draw(texture, entity_pos);
    //sprite_batch.draw(texture, model);
    game_window.swap_buffers();
  }

  return 0;
}
