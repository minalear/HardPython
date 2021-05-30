#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#include "glad/glad.h"
#include "logger.h"

minalear::Texture2D::Texture2D(const char *path) {
  auto data = stbi_load(path, &_width, &_height, &_nBits, STBI_rgb_alpha);

  minalear::log("==> Texture - %s", path);
  minalear::log("Dimensions: %d x %d", _width, _height);

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  // glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(data);
}

int minalear::Texture2D::width() {
  return _width;
}

int minalear::Texture2D::height() {
  return _height;
}

void minalear::Texture2D::bind() {
  glBindTexture(GL_TEXTURE_2D, id);
}