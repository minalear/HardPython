#include "particle_spawner.h"
#include "glm/glm.hpp"
#include "../core/logger.h"

ParticleSpawner::ParticleSpawner(glm::vec2 pos) :
  Entity(pos),
  particle_count(0),
  particle_texture("content/textures/particle.png"),
  timer(0.f) { }

void ParticleSpawner::update(float dt) {
  // particle spawning
  timer += dt;
  if (timer >= 0.2f) { 
    particles[particle_count].pos = pos; // assign partcle pos to parent pos
    particle_count += (particle_count != 1000) ? 1 : 0;
    timer -= 0.2f;
  }

  const glm::vec2 vel = glm::vec2(-100.f, 0.f) * dt;
  for (int i = 0; i < particle_count; i++) {
    particles[i].pos += vel;
  }
}

void ParticleSpawner::draw(minalear::SpriteBatch &sprite_batch) {
  for (int i = 0; i < particle_count; i++) {
    sprite_batch.draw(particle_texture, particles[i].pos, glm::vec2(1.f));
  }
}