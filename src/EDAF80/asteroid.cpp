#include "asteroid.hpp"

#include "EDAF80/parametric_shapes.hpp"


asteroid::asteroid(glm::vec3 pos, float radius){
  this->node = Node();
  this->mesh = parametric_shapes::createSphere(radius, RES, RES);
  this->node.set_geometry(this->mesh);
  this->node.get_transform().SetTranslate(pos);
}

asteroid make_asteroid(){
  return asteroid( {1,1,1}, 1.f);
}

