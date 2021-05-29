#include "world.h"
#include "../core/sprite_batch.h"

World::World() : entity_count(0) {
  entities = new Entity*[1000];
}

void World::add_entity(Entity *entity) {
  entities[entity_count++] = entity;
}

void World::update(float dt) {
  for (int i = 0; i < entity_count; i++) {
    entities[i]->update(dt);
  }
}
void World::draw(minalear::SpriteBatch &sprite_batch) {
  for (int i = 0; i < entity_count; i++) {
    entities[i]->draw(sprite_batch);
  }
}