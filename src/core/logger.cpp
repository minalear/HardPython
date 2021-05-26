#include "logger.h"
#include <cstdarg>

void (*logger)(const char*, ... );

void minalear::set_default_logger(void fnc(const char*, ... )) {
  logger = fnc;
}

void minalear::log(const char *msg, ... ) {
  logger(msg);
}