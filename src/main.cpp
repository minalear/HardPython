#include "core/window.h"

int main(int argc, char* argv[]) {
  auto game_window = minalear::GameWindow("Hard Python", 800, 480);

  SDL_Event window_event;
  while (true) {
    if (SDL_PollEvent(&window_event)) {
      if (window_event.type == SDL_QUIT) break;
    }

    game_window.dt();
    game_window.swap_buffers();
  }

  return 0;
}