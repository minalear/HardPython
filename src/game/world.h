#ifndef MINALEAR_WORLD_H
#define MINALEAR_WORLD_H

#include "entity.h"
#include "../core/sprite_batch.h"

class World {
  Entity **entities;
  int entity_count;

public:
  World();
  
  void add_entity(Entity *entity);

  void update(float dt);
  void draw(minalear::SpriteBatch &sprite_batch);
};

#endif