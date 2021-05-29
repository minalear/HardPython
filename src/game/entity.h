#ifndef MINALEAR_ENTITY_H
#define MINALEAR_ENTITY_H

#include "glm/glm.hpp"
#include "../core/sprite_batch.h"
#include "../core/texture.h"

class Entity {
protected:
  glm::vec2 pos;
  glm::vec2 vel;

public:
  Entity();
  Entity(glm::vec2 pos);

  void debug_draw(minalear::SpriteBatch &sb, minalear::Texture2D &text);
  virtual void draw(minalear::SpriteBatch &sb);
  virtual void update(float dt);

  void apply_force(glm::vec2 impulse);

  glm::vec2 position();
  glm::vec2 velocity();
};

#endif