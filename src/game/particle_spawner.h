#ifndef MINALEAR_PARTICLE_SPAWNER_H
#define MINALEAR_PARTICLE_SPAWNER_H

#include "entity.h"
#include "../core/sprite_batch.h"
#include "../core/texture.h"
#include "../core/event/event.h"

struct Particle {
  glm::vec2 pos;
};

class ParticleSpawner : public Entity {
  Particle particles[1000];
  int particle_count;
  minalear::Texture2D particle_texture;
  float timer;

  void event_callback(const minalear::Event& event);

public:
  ParticleSpawner(glm::vec2 pos);

  void update(float dt);
  void draw(minalear::SpriteBatch &sprite_batch);
};

#endif