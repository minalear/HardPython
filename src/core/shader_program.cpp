#include <cstdio>
#include "glad/glad.h"
#include "shader_program.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

bool checkShaderCompilation(GLuint shader_id) {
  GLint compileStatus = 0;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compileStatus);

  if (compileStatus == GL_FALSE) {
    GLchar error_message[512];
    glGetShaderInfoLog(shader_id, 512, nullptr, error_message);
    printf("Shader Compilation Error, %s\n", error_message);
  }

  return bool(compileStatus);
}

minalear::ShaderProgram::ShaderProgram(const char *v_source, const char *f_source) {
  program_id = glCreateProgram();

  // vertex shader
  GLuint v_shader_id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(v_shader_id, 1, &v_source, nullptr);
  glCompileShader(v_shader_id);
  checkShaderCompilation(v_shader_id);

  // fragment shader
  GLuint f_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(f_shader_id, 1, &f_source, nullptr);
  glCompileShader(f_shader_id);
  checkShaderCompilation(f_shader_id);

  glAttachShader(program_id, v_shader_id);
  glAttachShader(program_id, f_shader_id);
  glLinkProgram(program_id);

  // TODO: check link status

  glDetachShader(program_id, v_shader_id);
  glDetachShader(program_id, f_shader_id);
  glDeleteShader(v_shader_id);
  glDeleteShader(f_shader_id);
}

GLuint minalear::ShaderProgram::id() {
  return program_id;
}

void minalear::ShaderProgram::use() {
  glUseProgram(program_id);
}

int32_t minalear::ShaderProgram::get_uniform_location(const char *name) {
  // inserts the name and returns the uniform location if it doesn't exist in the map
  if (uniform_map.find(name) == uniform_map.end()) {
    int loc = glGetUniformLocation(program_id, name);
    uniform_map.insert(ShaderUniformLoc(name, loc));

    return loc;
  }

  return uniform_map[name];
}

void minalear::ShaderProgram::set_uniform(const char *name, bool value) {
  glUniform1i(get_uniform_location(name), value);
}

void minalear::ShaderProgram::set_uniform(const char *name, glm::vec2 &value) {
  glUniform2f(get_uniform_location(name), value.x, value.y);
}

void minalear::ShaderProgram::set_uniform(const char *name, glm::vec3 &value) {
  glUniform3f(get_uniform_location(name), value.x, value.y, value.z);
}

void minalear::ShaderProgram::set_uniform(const char *name, glm::vec4 &value) {
  glUniform4f(get_uniform_location(name), value.x, value.y, value.z, value.w);
}

void minalear::ShaderProgram::set_uniform(const char *name, glm::mat4 &value) {
  glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(value));
}