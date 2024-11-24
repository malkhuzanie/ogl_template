#ifndef COMPONENT_H
#define COMPONENT_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <memory>
#include <vector>

#include <texture.h>
#include <utils.h>
#include <transform.h>

class Component {
public:
    std::vector<glm::vec4> transformed_vertex;
    std::vector<glm::vec4> vertex;
};

class Renderable : public Component, public Transform {
public:
    virtual void build(GLenum);
    void texture_repeat(const int& xr, const int& yr);
    virtual void texture_repeat(const int& xr, const int& yr, const int& face);

    unsigned int offset;
    unsigned int list_id;

    std::vector<Texture> texture;
    std::vector<glm::vec2> tex_cor; 
    glm::vec3 colour = {255, 255, 255};
};

class Shape : public Renderable {
public:
    void render();

    GLenum type;
};

class Rectangle : public Shape {
public:
    Rectangle(const glm::vec2& p, const float& w, const float& h);
    Rectangle(const float& w, const float& h);
};

class Circle : public Shape {
public:
    using T = float;
    Circle(const std::pair<T, T>& center, const T& radius, int count = 128);
    Circle(const T& radius, int count = 512);

    static std::vector<glm::vec3> gen_vertices(const T& radius, int count = 512);
};

class Sphere : public Shape {
public: 
    Sphere(const float& radius, const int& stacks, const int& slices);
};

class Cube : public Shape {
public:
    Cube(const glm::vec3& p, const double& length);
    Cube(const double& length);

    void texture_repeat(const int& xr, const int& yr, const int& face);
};


#endif
