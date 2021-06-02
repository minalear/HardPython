#include <cstdio>
#include <cstdarg>
#include <functional>

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

#include "glad/glad.h"
#include "core/window.h"
#include "core/sprite_batch.h"
#include "core/texture.h"
#include "core/logger.h"
#include "core/input.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "core/event/event.h"

#include "game/entity.h"
#include "game/world.h"
#include "game/particle_spawner.h"

// standard logger for program
void fmt_logger(const char* msg, va_list args) {
  vprintf(msg, args);
  putchar('\n');
}

int main(int argc, char* argv[]) {
  SDL_SetMainReady();

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

  float timer = game_window.dt();
  const float step = 0.01667f;

  SDL_Event window_event;
  while (true) {
    // handle input
    minalear::handle_input();
    if (SDL_PollEvent(&window_event)) {
      if (window_event.type == SDL_QUIT) break;
      if (minalear::key_down(SDL_SCANCODE_ESCAPE)) break;
    }

    // update logic
    timer += game_window.dt();
    if (timer >= step) {
      timer -= step;
    }

    // rendering logic
    glClear(GL_COLOR_BUFFER_BIT);

    game_window.swap_buffers();
  }

  return 0;
}

// TODO: Checklist
// ContentManager - singleton for loading and unloading content that can be referenced around the codebase
// ECS - entity/component system for efficiently storing entity data