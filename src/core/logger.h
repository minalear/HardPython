#ifndef MINALEAR_LOGGER_H
#define MINALEAR_LOGGER_H

#include <cstdarg>

namespace minalear {
  void set_default_logger(void fnc(const char*, va_list args ));
  void log(const char* msg, ... );
}


#endif