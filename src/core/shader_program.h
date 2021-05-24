#ifndef MINALEAR_SHADER_H
#define MINALEAR_SHADER_H

#include <map>
#include "glad/glad.h"
#include "glm/glm.hpp"

typedef std::pair<const char*, int> ShaderUniformLoc;

namespace minalear {
  class ShaderProgram {
    GLuint program_id;

    std::map<const char*, int> uniform_map;
    int32_t get_uniform_location(const char* name);

    public:
      ShaderProgram(const char*, const char*);

      GLuint id();
      void use();

      void set_uniform(const char* name, bool value);
      void set_uniform(const char* name, glm::vec2 &value);
      void set_uniform(const char* name, glm::vec3 &value);
      void set_uniform(const char* name, glm::vec4 &value);
      void set_uniform(const char* name, glm::mat4 &value);
  };
}

#endif