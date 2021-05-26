#include <cstdio>
#include <cstdarg>

#include "glad/glad.h"
#include "core/window.h"
#include "core/sprite_batch.h"
#include "core/texture.h"
#include "core/logger.h"

// standard logger for program
void fmt_logger(const char* msg, va_list args) {
  vprintf(msg, args);
  putchar('\n');
}

int main(int argc, char* argv[]) {
  minalear::set_default_logger(fmt_logger);
  
  auto game_window = minalear::GameWindow("Hard Python", 1280, 720);

  // setup blend/clear color
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glViewport(0, 0, game_window.width(), game_window.height());

  auto sprite_batch = minalear::SpriteBatch();
  auto texture = minalear::Texture2D("content/textures/placeholder.png");

  SDL_Event window_event;
  while (true) {
    if (SDL_PollEvent(&window_event)) {
      if (window_event.type == SDL_QUIT) break;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    sprite_batch.draw(texture, glm::vec2(400.f, 0.f));

    game_window.dt();
    game_window.swap_buffers();
  }

  return 0;
}