#include "glm/glm.hpp"
#include "../core/sprite_batch.h"
#include "../core/texture.h"
#include "entity.h"

using namespace minalear;

Entity::Entity() : pos(glm::vec2(0.f)), vel(glm::vec2(0.f)) { }
Entity::Entity(glm::vec2 pos) : pos(pos), vel(glm::vec2(0.f)) { }

void Entity::debug_draw(SpriteBatch &sb, Texture2D &text) {
  sb.draw(text, pos);
}
void Entity::draw(SpriteBatch &sb) { }
void Entity::update(float dt) {
  pos = pos + vel * dt;
}

void Entity::apply_force(glm::vec2 impulse) {
  vel += impulse;
}
glm::vec2 Entity::position() {
  return pos;
}
glm::vec2 Entity::velocity() {
  return vel;
}