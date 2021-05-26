#include "logger.h"
#include <cstdarg>

void (*logger)(const char*, va_list args );

void minalear::set_default_logger(void fnc(const char*, va_list args )) {
  logger = fnc;
}

void minalear::log(const char *msg, ... ) {
  va_list args;
  va_start(args, msg);
  logger(msg, args);
  va_end(args);
}