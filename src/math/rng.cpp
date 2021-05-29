#include <cstdlib>
#include <ctime>
#include "rng.h"

void rng::init() {
  srand(time(NULL));
}

int rng::next_int() {
  return rand();
}
int rng::next_int(int max) {
  return rand() % max;
}
int rng::next_int(int min, int max) {
  return rand() % (max - min) + min;
}