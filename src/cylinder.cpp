#include <cylinder.h>

Cylinder::Cylinder(const int& count)
{
    for (size_t i = 0; i < count; ++i) {
        tex_cor.emplace_back(0, 1);
        tex_cor.emplace_back(0, 0);
        tex_cor.emplace_back(1, 0);
        tex_cor.emplace_back(1, 1);
    }
}

std::vector<glm::vec4> Cylinder::gen_vertices()
{
    std::vector<glm::vec4> coord;
    auto h = height / 2;
    const float angle = 360.0f / (float) count;
    for (auto i = 0; i < count; ++i) {
        auto theta = angle * (float) i;
        auto x = radius * cos(glm::radians(theta));
        auto z = radius * sin(glm::radians(theta));
        coord.emplace_back(x, + h, z, 1);
        coord.emplace_back(x, - h, z, 1);
    }
    return coord;
}

Cylinder::Cylinder(const float& b_radius, const float& t_radius,
                   const float& height, int count) 
    : Cylinder(count)
{
    std::vector<glm::vec3> base = Circle::gen_vertices(b_radius, count);
    std::vector<glm::vec3> top  = Circle::gen_vertices(t_radius, count);

    base.emplace_back(base[0]);
    top.emplace_back(top[0]);

    float h = height / 2;
    for (int i = 0; i < count; ++i) {
        vertex.emplace_back(base[i].x, - h, base[i].z, 1);
        vertex.emplace_back(top[i].x , + h, top[i].z, 1);
        vertex.emplace_back(top[i + 1].x , + h, top[i + 1].z, 1);
        vertex.emplace_back(base[i + 1].x, - h, base[i + 1].z, 1);
    }

    offset = 4;
    type = GL_TRIANGLE_FAN;
}

Cylinder::Cylinder(const float& radius, const float& height, int count)
    : radius {radius},
      height {height},
      count  {count}
{
    std::vector<glm::vec4> coord = gen_vertices();

    for (int i = 0; i < (int) coord.size(); ++i) {
        if (!(i & 1)) vertex.emplace_back(coord[i]);
    }
    vertex.emplace_back(coord[0]);
    for (int i = 0; i < (int) coord.size(); ++i) {
        if (i & 1) vertex.emplace_back(coord[i]);
    }
    vertex.emplace_back(coord[1]);

    coord.resize(0);
    for (int i = 0; i < count; ++i) {
        coord.emplace_back(vertex[i]);
        coord.emplace_back(vertex[i + count + 1]);
        coord.emplace_back(vertex[i + count + 2]);
        coord.emplace_back(vertex[i + 1]);
    }

    vertex = coord;
    offset = 4;

    for (size_t i = 0; i < count; ++i) {
        tex_cor.emplace_back(0, 1);
        tex_cor.emplace_back(0, 0);
        tex_cor.emplace_back(1, 0);
        tex_cor.emplace_back(1, 1);
    }

    type = GL_TRIANGLE_FAN;
}
