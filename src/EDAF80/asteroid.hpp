#pragma once

#include "assignment5.hpp"
#include "config.hpp"
#include "core/Bonobo.h"
#include "core/FPSCamera.h"
#include "core/helpers.hpp"
#include "core/ShaderProgramManager.hpp"

#include <imgui.h>
#include <tinyfiledialogs.h>

#include <clocale>
#include <stdexcept>
#include <vector>
#include "core/node.hpp"

struct sphere{
  glm::vec3 pos;
  glm::vec3 vel;
  glm::vec3 acc;
  float radius;
  Node node;
  sphere(glm::vec3 pos, float r, glm::vec3 vel):pos(pos), vel(vel), radius(r){}
  void update_pos(float dt){pos = pos + vel*dt; node.get_transform().SetTranslate(pos);};
  void update_vel(float dt){vel = vel + acc*dt;};
};

struct bullet:sphere{
  static const unsigned int RES = 5;
  bullet(glm::vec3 pos, glm::vec3 vel);
private:
  
  bonobo::mesh_data mesh;
};

struct asteroid: sphere {
  static const unsigned int RES = 10;
  asteroid(glm::vec3 pos, float r, glm::vec3 vel); 
  void collision(const asteroid &);
  int id; 
private:
  bonobo::mesh_data mesh;
  static int count;
};

asteroid generate_asteroid();
bullet generate_bullet(glm::vec3 pos, glm::vec3 vel);
glm::vec3 generate_asteroid_position();
glm::vec3 generate_asteroid_velocity(const glm::vec3& );
float generate_asteroid_radius();
bool test_collision(const sphere& a, const sphere& b );


