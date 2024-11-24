#ifndef ENTITY_H
#define ENTITY_H

#include <component.h>
#include <cylinder.h>

struct Entity {
    void add(std::shared_ptr<Shape> component, const Transform& tr = {}, 
            const glm::vec3& cl = {255, 255, 255});

    void add(const Entity& ent, const Transform& tr = {}, 
            const glm::vec3& cl = {255, 255, 255});

    void build();
    void render();
    unsigned int size();

    const std::vector<std::shared_ptr<Shape>>& data();

    Transform transform;

    std::vector<std::shared_ptr<Shape>> component;
    std::vector<Transform> trans;
    std::vector<glm::vec3> colour;
};

#endif
