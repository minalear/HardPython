#ifndef MINALEAR_SHADERS_H
#define MINALEAR_SHADERS_H

const char* VERTEX_SHADER_SOURCE = 
  "#version 400\n"
  "layout(location = 0) in vec2 aPos;\n"
  "layout(location = 1) in vec2 aUV;\n"
  "layout(location = 2) in vec3 aColor;\n"

  "out vec2 UV;\n"
  "out vec3 Color;\n"

  "uniform mat4 proj;\n"
  "uniform mat4 view;\n"
  "uniform mat4 model;\n"

  "void main() {\n"
  "  UV = aUV;\n"
  "  Color = aColor;\n"
  "  gl_Position = proj * view * model * vec4(aPos, 0.0, 1.0);\n"
  "}"
;

const char* FRAGMENT_SHADER_SOURCE = 
  "#version 400\n"
  "in vec2 UV;\n"
  "in vec3 Color;\n"

  "out vec4 fragment_color;\n"

  "uniform sampler2D image;\n"

  "void main() {\n"
  "  vec4 sampled_color = texture(image, UV);\n"
  "  fragment_color = sampled_color * vec4(Color, 1.0);\n"
  "}"
;

#endif