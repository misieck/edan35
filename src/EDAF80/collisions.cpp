#include <iostream>
#include <glm/gtx/io.hpp>
#include <random>  
#include <glm/glm.hpp>
#include <cmath> 

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



glm::vec3 generate_asteroid_position();
float generate_asteroid_radius();
glm::vec3 generate_asteroid_velocity(glm::vec3);


struct Vector {
    float x, y, z;
};

struct Point {
    float x, y, z;
    Vector operator-(const Point& b){
      return {x - b.x, y - b.y, z - b.z};
    }
};


struct Sphere {
    Point position; 
    float radius;
};

// Dot product of two vectors
float Dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Test if ray intersects sphere
int TestRaySphere(Point p, Vector d, Sphere s);

int main() {
    // Example usage
    Point rayOrigin = {0.0f, 0.0f, 0.0f};
    Vector rayDirection = {1.0f, 1.0f, 0.0f}; // Ray pointing along the x-axis
    Sphere sphere = {{-1.0f, -1.0f, 0.0f}, 0.4f}; // Sphere at (1, 0, 0) with radius 1.0

    int result = TestRaySphere(rayOrigin, rayDirection, sphere);

    if (result)
        std::cout << "Ray intersects the sphere." << std::endl;
    else
        std::cout << "Ray does not intersect the sphere." << std::endl;



    //tester for the functions 
    std::srand(static_cast<unsigned>(std::time(0)));
    glm::vec3 position;
    float radius;
    glm::vec3 velocity;

    for(int i = 0; i < 10; i++){
        position = generate_asteroid_position();
        radius = generate_asteroid_radius();
        velocity = generate_asteroid_velocity(position);

        printf("Position %f,%f,%f\n", position.x, position.y, position.z);
        printf("Velocity %f,%f,%f\n", velocity.x, velocity.y, velocity.z);
        printf("Radius %f\n", radius);
        printf("\n");
    }




    return 0;
}

// Test if ray r = p + td intersects sphere s
int TestRaySphere(Point p, Vector d, Sphere s) {
    Vector m = {p.x - s.position.x, p.y - s.position.y, p.z - s.position.z};
    float c = Dot(m, m) - s.radius * s.radius;

    if (c <= 0.0f)
        return 1;

    float b = Dot(m, d);

    if (b > 0.0f)
        return 0;

    float disc = b * b - c;

    if (disc < 0.0f)
        return 0;

    return 1;
}

bool TestSphereSphere(Sphere a, Sphere b) {
    // Calculate squared distance between centers
    Vector d = a.position - b.position; //{a.position.x - b.position.x, a.position.y - b.position.y, a.position.z - b.position.z};
    float squaredDistance = Dot(d, d); // Same as d.LengthSquared()

    // Spheres intersect if squared distance is less than squared sum of radii
    float radiusSum = a.radius + b.radius;
    float squaredRadii = radiusSum * radiusSum;

    return squaredDistance <= squaredRadii;
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

glm::vec3 generate_asteroid_velocity(glm::vec3 position){

    
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