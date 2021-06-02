#include <cstdio>
#include <functional>

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

#include "glad/glad.h"
#include "core/window.h"
#include "core/sprite_batch.h"
#include "core/logger.h"
#include "core/input.h"

#include "core/event/event.h"

// standard logger for program
void fmt_logger(const char* msg, va_list args) {
  vprintf(msg, args);
  putchar('\n');
}

void callback(const minalear::Event& event) {
  if (event.type == minalear::EventType::KeyUp) {
    minalear::log("key up: %u", event.key.scancode);
  } else if (event.type == minalear::EventType::KeyDown) {
    minalear::log("key down: %u, repeat: %s", event.key.scancode, event.key.repeat ? "true" : "false");
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

  float timer = game_window.dt();
  const float step = 0.01667f;

  using minalear::EventType;
  using minalear::Event;
  using minalear::KeyboardEvent;

  minalear::g_EventHandler.Subscribe(callback);

  SDL_Event window_event;
  while (true) {
    // handle input
    minalear::handle_input();
    if (SDL_PollEvent(&window_event)) {
      if (window_event.type == SDL_QUIT) break;
      else if (window_event.type == SDL_KEYUP) {
        Event event = Event(EventType::KeyUp);
        event.key = KeyboardEvent { window_event.key.keysym.scancode, false };
        minalear::g_EventHandler.Post(event);
      } else if (window_event.type == SDL_KEYDOWN) {
        if (window_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) break; // quit game
        Event event = Event(EventType::KeyDown);
        event.key = KeyboardEvent {
          window_event.key.keysym.scancode, // Scancode
          bool(window_event.key.repeat) // Repeat
        };
        minalear::g_EventHandler.Post(event);
      }
    }

    // update logic
    timer += game_window.dt();
    if (timer >= step) {
      timer -= step;

      Event event = Event(EventType::Tick);
      event.tick = minalear::TickEvent();
      minalear::g_EventHandler.Post(event);
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