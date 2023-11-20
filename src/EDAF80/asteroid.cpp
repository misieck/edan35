#include "asteroid.hpp"
#include <glm/ext/quaternion_geometric.hpp>
#include <iostream>
#include <ostream>
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
#define min_velocity_norm 3
#define max_velocity_norm 10

int asteroid::count = 0;


bullet::bullet(glm::vec3 pos, glm::vec3 vel):sphere(pos, 0.06f, vel){
  this->mesh = parametric_shapes::createSphere(radius, RES, RES);
  this->node.set_geometry(this->mesh);
}


asteroid::asteroid(glm::vec3 pos, float radius, glm::vec3 vel):sphere(pos,radius,vel){
  this->mesh = parametric_shapes::createSphere(radius, RES, RES);
  this->node.set_geometry(this->mesh);
  this->id = ++count; 
}

asteroid generate_asteroid(){
  auto pos = generate_asteroid_position();
  return asteroid( pos,
                   generate_asteroid_radius(),
                   glm::vec3(0,0,0) //generate_asteroid_velocity(pos)
                  );
}

bullet generate_bullet(glm::vec3 pos, glm::vec3 dir){
    return bullet(pos, dir*10.0f);
}

//TODO: add a bit of randomness to the collision

void asteroid::collision(const asteroid& b){
  //auto small_ball = parametric_shapes::createSphere(0.3, RES, RES);
  //node.set_geometry(small_ball);
  
  glm::vec3 dx = this->pos - b.pos;
  auto len_dx = glm::length(dx);
  glm::vec3 dv = this->vel - b.vel;
  float m1 = this->radius*this->radius*this->radius*4.f;
  float m2 = b.radius*b.radius*b.radius*4.f;
  float mass_factor = 2*m2/(m1+m2);
  glm::vec3 new_v = this->vel - (mass_factor * glm::dot(dv, dx) / len_dx / len_dx ) * dx;
  this->vel = new_v;
  
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


bool test_collision(const sphere& a, const sphere& b ){
  if (glm::dot(a.vel, b.vel) < 0 ) return false;
  glm::vec3 d = a.pos - b.pos;
  float squared_distance = glm::dot(d,d);

  float squaredRadii = (a.radius+b.radius) * (a.radius+b.radius);

  
  return squared_distance<=squaredRadii;
  
  
}
