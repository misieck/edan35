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

struct asteroid {
  static const unsigned int RES = 10;
  
  Node node;
  glm::vec3 pos;
  glm::vec3 vel;
  glm::vec3 acc;
  float radius;
  asteroid(glm::vec3 pos, float r);
  void update_pos(float dt){pos = pos + vel*dt;};
  void update_vel(float dt){vel = vel + acc*dt;};
private:
  bonobo::mesh_data mesh;
};

asteroid make_asteroid();

