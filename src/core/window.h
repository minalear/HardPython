#ifndef MINALEAR_WINDOW_H
#define MINALEAR_WINDOW_H

#include "SDL2/SDL.h"

namespace minalear {
  const int OPENGL_MAJOR_VERSION = 4;
  const int OPENGL_MINOR_VERSION = 0;

  class GameWindow {
    uint32_t client_width;
    uint32_t client_height;
    uint32_t start_time;

    SDL_Window *sdl_window;
    SDL_GLContext gl_context;

    public:
      GameWindow(const char* title, uint32_t width, uint32_t height);
      ~GameWindow();

      uint32_t  width();
      uint32_t  height();
      float dt();
      void swap_buffers();
  };
}

#endif