#include "asteroid.hpp"
#include <random>
#include <cmath>
#include "EDAF80/parametric_shapes.hpp"

#define max_theta 90 
#define min_theta 0
#define max_phi 90 
#define min_phi 0
#define max_ro 100 
#define min_ro 30
#define max_z 50
#define min_ast_size 1
#define max_ast_size 4
#define close_radius 10
#define min_velocity_norm 1
#define max_velocity_norm 3


asteroid::asteroid(glm::vec3 pos, float radius, glm::vec3 vel){
  this->node = Node();
  this->mesh = parametric_shapes::createSphere(radius, RES, RES);
  this->node.set_geometry(this->mesh);
  this->pos = pos;
  this->vel = vel;
}

asteroid generate_asteroid(){
  auto pos = generate_asteroid_position();
  return asteroid( pos,
                   generate_asteroid_radius(),
                   generate_asteroid_velocity(pos)
                  );
}


glm::vec3 generate_asteroid_position(){

    
    float ro =  min_ro + (rand() % (max_ro - min_ro));
    float theta = (rand() % (max_theta - min_theta)) - ((max_theta - min_theta) / 2.0 );
    float phi = (rand() % (max_phi - min_phi)) - ((max_phi - min_phi) / 2.0 );

    return {ro * cos(theta * M_PI / 180.0 ), ro * sin(theta * M_PI / 180.0), -ro * sin(phi * M_PI / 180.0)}; 
}

float generate_asteroid_radius(){

    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min_ast_size, max_ast_size);

    // Generate a random float between 1 and 4
    return dis(gen);
}

glm::vec3 generate_asteroid_velocity(const glm::vec3& position){
    
    float theta = rand() % (max_theta - min_theta) - ((max_theta - min_theta) / 2.0);
    float phi = rand() % (max_phi - min_phi) - ((max_phi - min_phi) / 2.0);
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min_velocity_norm, max_velocity_norm);
    float velocity_norm = dis(gen);

    glm::vec3 velocity = {close_radius * cos(theta * M_PI / 180.0) - position. x, 
                          close_radius * sin(theta * M_PI / 180.0) - position.y, 
                          -close_radius * cos(phi * M_PI / 180.0) - position.z};



    return glm::normalize(velocity) * velocity_norm; 
}
