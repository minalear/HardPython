#include <iostream>
#include <cassert>
#include "SDL2/SDL.h"
#include "glad/glad.h"
#include "window.h"
#include "logger.h"

minalear::GameWindow::GameWindow(const char *title, uint32_t width, uint32_t height) {
  // Initialize SDL and create a window
  SDL_Init(SDL_INIT_VIDEO);

  // Set SDL OpenGL attributes (core profile, opengl v4.0)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);

  // Set multisampling
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

  // SDL_GL_SetSwapInterval(0); // vsync

  // handle high dpi sizing
  float dpi = 96.0f;
  /*if (SDL_GetDisplayDPI(0, NULL, &dpi, NULL) != 0 || dpi == 0.f) {
    printf("Failed to get DPI info: %f\n", dpi);
    dpi = 96.f; // default to standard
  }*/

  client_width = int(width * dpi / 96.0f);
  client_height = int(height * dpi / 96.0f);
  
  minalear::log(
    "======================================\n"
    "SDL Window created with OpenGL context\n"
    "Dimensions (%d, %d)\n"
    "DPI %f\n"
    "======================================",
    client_width, client_height, dpi
  );

  sdl_window = SDL_CreateWindow(
    title,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    client_width, client_height,
    SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI
  );

  // TODO: Error checking for window and context creation

  gl_context = SDL_GL_CreateContext(sdl_window);
  start_time = SDL_GetTicks(); // used to calculate time delta

  int gladLoadSuccess = gladLoadGLLoader(SDL_GL_GetProcAddress);
  assert(gladLoadSuccess);
}

minalear::GameWindow::~GameWindow() {
  SDL_GL_DeleteContext(gl_context);
  SDL_Quit();
}

uint32_t minalear::GameWindow::width() {
  return client_width;
}

uint32_t minalear::GameWindow::height() {
  return client_height;
}

/// Call once per frame to calculate the time delta from the previous frame
float minalear::GameWindow::dt() {
  uint32_t ticks = SDL_GetTicks() - start_time;
  float dt = ticks * 0.001f; // ms to s
  start_time = SDL_GetTicks();

  return dt;
}

void minalear::GameWindow::swap_buffers() {
  SDL_GL_SwapWindow(sdl_window);
}