#include <cstdio>
#include <cstdarg>

#include "glad/glad.h"
#include "core/window.h"
#include "core/sprite_batch.h"
#include "core/texture.h"
#include "core/logger.h"
#include "core/input.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "game/entity.h"
#include "game/world.h"
#include "game/particle_spawner.h"

// standard logger for program
void fmt_logger(const char* msg, va_list args) {
  vprintf(msg, args);
  putchar('\n');
}

float vec_len_sqr(glm::vec2 vec) {
  return (vec.x * vec.x + vec.y * vec.y);
}

int main(int argc, char* argv[]) {
  minalear::set_default_logger(fmt_logger);
 
  const int viewport_width = 1280;
  const int viewport_height = 720;
  auto game_window = minalear::GameWindow("Hard Python", viewport_width, viewport_height);
  minalear::init_input();

  // setup blend/clear color
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.f, 0.f, 0.f, 1.f);
  //glViewport(0, 0, game_window.width(), game_window.height());
  //glViewport(0, 0, viewport_width, viewport_height);

  auto sprite_batch = minalear::SpriteBatch(viewport_width, viewport_height);
  auto texture = minalear::Texture2D("content/textures/placeholder.png");

  float dt = game_window.dt();
  const float update_step = 0.01667f;

  glm::vec2 entity_pos = glm::vec2(0.f, 0.f);
  //glm::mat4 model = glm::scale(glm::mat4(1.f), glm::vec3(viewport_width, viewport_height, 1.f));
  glm::mat4 model = glm::scale(glm::mat4(1.f), glm::vec3(512.f, 512.f, 1.f));

  Entity entities[] = {
    Entity(glm::vec2(0.f, 0.f))
  };

  World world;
  const glm::vec2 pos = glm::vec2(viewport_width, viewport_height) * 0.5f;
  minalear::log("New particle spawner at: (%f, %f)", pos.x, pos.y);
  world.add_entity(new ParticleSpawner(pos));

  SDL_Event window_event;
  while (true) {
    // handle input
    minalear::handle_input();
    if (SDL_PollEvent(&window_event)) {
      if (window_event.type == SDL_QUIT) break;
      if (minalear::key_down(SDL_SCANCODE_ESCAPE)) break;
    }

    // update logic
    dt += game_window.dt();
    if (dt >= update_step) {
      dt -= update_step;
      world.update(dt);

      const float speed = 50.f;
      if (minalear::key_down(SDL_SCANCODE_A)) {
        entities[0].apply_force(glm::vec2(-speed, 0.f));
      }
      if (minalear::key_down(SDL_SCANCODE_D)) {
        entities[0].apply_force(glm::vec2(speed, 0.f));
      }

      if (minalear::key_down(SDL_SCANCODE_SPACE)) {
        //minalear::log("pos: %fx%f", entity_pos.x, entity_pos.y);
        entities[0].apply_force(glm::vec2(0.f, -30.f));
      }
    }

    // update entities
    /*for (int i = 0; i < sizeof(entities) / sizeof(entities[0]); i++) {
      // apply friction
      glm::vec2 friction = entities[i].velocity();
      if (vec_len_sqr(friction) != 0.f) {
        friction = glm::normalize(friction) * -1.f;
        entities[i].apply_force(friction);

        const glm::vec2 vel = entities[i].velocity();
        //minalear::log("friction: (%f, %f)", friction.x, friction.y);
        //minalear::log("velocity: (%f, %f)", vel.x, vel.y);
      }

      // apply gravity
      entities[i].apply_force(glm::vec2(0.f, 9.8f));
      entities[i].update(dt);
    }*/

    // rendering logic
    glClear(GL_COLOR_BUFFER_BIT);
    //sprite_batch.draw(texture, entity_pos);
    /*for (int i = 0; i < sizeof(entities) / sizeof(entities[0]); i++) {
      entities[i].debug_draw(sprite_batch, texture);
    }*/
    world.draw(sprite_batch);
    game_window.swap_buffers();
  }

  return 0;
}
