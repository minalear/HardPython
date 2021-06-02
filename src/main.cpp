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

int ticks = 0;
auto dispatcher = minalear::EventDispatcher();

// standard logger for program
void fmt_logger(const char* msg, va_list args) {
  vprintf(msg, args);
  putchar('\n');
}

void event_callback(const minalear::Event& event) {
  if (event.type == minalear::EventType::Tick) {
    ticks++;
    minalear::log("tick: %d", ticks);
    if (ticks >= 1000) {
      dispatcher.Post(minalear::ForceQuit());
    }
  }
}


void other_callback(const minalear::Event& event) {
  if (event.type == minalear::EventType::ForceQuit) {
    exit(1);
  }
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
  auto texture = minalear::Texture2D("content/textures/placeholder.png");

  float timer = game_window.dt();
  const float dt = 0.01667f;

  //dispatcher.Subscribe(event_callback);
  //dispatcher.Subscribe(other_callback);

  auto spawner = ParticleSpawner(glm::vec2(640.f, 480.f));

  SDL_Event window_event;
  while (true) {
    // handle input
    minalear::handle_input();
    if (SDL_PollEvent(&window_event)) {
      if (window_event.type == SDL_QUIT) break;
      if (minalear::key_down(SDL_SCANCODE_ESCAPE)) break;

      if (window_event.type == SDL_MOUSEMOTION) {
        dispatcher.Post(
          minalear::MouseMoveEvent(glm::vec2( float(window_event.motion.x), float(window_event.motion.y) ))
        );
      }
    }

    // update logic
    timer += game_window.dt();
    if (timer >= dt) {
      timer -= dt;
      dispatcher.Post(minalear::TickEvent());
      spawner.update(dt);
    }

    // rendering logic
    glClear(GL_COLOR_BUFFER_BIT);
    spawner.draw(sprite_batch);
    game_window.swap_buffers();
  }

  return 0;
}
