#include <iostream>
#include "SDL2/SDL.h"

int main() {
  SDL_Window *window;
  SDL_GLContext context;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  float dpi = 96.0f;
  if (SDL_GetDisplayDPI(0, NULL, &dpi, NULL) != 0) {
    printf("Failed to get DPI info: %f\n", dpi);
    exit(1);
  }

  int window_width = int(1280.0f * dpi / 96.0f);
  int window_height = int(720.0f * dpi / 96.0f);

  window = SDL_CreateWindow(
    "Mingen Window",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    window_width, window_height,
    SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
  );

  SDL_Event window_event;
  while (true) {
    if (SDL_PollEvent(&window_event)) {
      if (window_event.type == SDL_QUIT) break;
    }

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DeleteContext(context);
  SDL_Quit();

  return 0;
}
