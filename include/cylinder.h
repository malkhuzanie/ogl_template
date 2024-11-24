#include <component.h>


class Cylinder : public Shape {
public:
    Cylinder(const float& b_radius, const float& t_radius, const float& height,
             int count);
    Cylinder(const float& radius, const float& height, int count = 512);
    std::vector<glm::vec4> gen_vertices();

    float radius;
    float height;
    int count;
private:
    Cylinder(const int& count);
};
