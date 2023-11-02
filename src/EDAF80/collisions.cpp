#include <iostream>


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
