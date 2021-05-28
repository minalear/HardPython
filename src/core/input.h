#ifndef MINALEAR_INPUT_H
#define MINALEAR_INPUT_H

#include <cstdint>

namespace minalear {
  void init_input();
  void handle_input();

  bool key_down(uint8_t keycode);
  bool key_up(uint8_t keycode);
}

#endif
