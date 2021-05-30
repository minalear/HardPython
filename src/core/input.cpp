#include <cstring>
#include "input.h"
#include "SDL2/SDL.h"
#include "logger.h"

uint8_t keyboard_state[SDL_NUM_SCANCODES];

void minalear::init_input() {
  //memcpy(keyboard_state, SDL_GetKeyboardState(nullptr), sizeof(keyboard_state));
  handle_input();
}

void minalear::handle_input() {
  SDL_PumpEvents();
  memcpy(keyboard_state, SDL_GetKeyboardState(nullptr), sizeof(keyboard_state));
}

bool minalear::key_down(uint8_t keycode) {
  return keyboard_state[keycode];
}

bool minalear::key_up(uint8_t keycode) {
  return !keyboard_state[keycode];
}