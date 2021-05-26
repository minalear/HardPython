#ifndef MINALEAR_LOGGER_H
#define MINALEAR_LOGGER_H

namespace minalear {
  void set_default_logger(void fnc(const char*, ... ));
  void log(const char* msg, ... );
}


#endif