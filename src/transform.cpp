#include <transform.h>

Transform::Transform() 
    : translate {0, 0, 0},
      scale {1, 1, 1},
      rotate {0, 0, 0}
{
}

Transform::Transform(const glm::vec3& translate, const glm::vec3& scale, 
        const glm::vec3& rotate)
{
    this->translate = translate;
    this->scale = scale;
    this->rotate = rotate;
}

std::vector<glm::vec4> Transform::transform(const std::vector<glm::vec4>& vertex)
{
    auto transform = glm::mat4(1.0f);
    transform = glm::translate(transform, translate);
    transform = glm::rotate(transform, glm::radians(rotate.x), glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, glm::radians(rotate.y), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(rotate.z), glm::vec3(0, 0, 1));
    transform = glm::scale(transform, scale);

    std::vector<glm::vec4> transformed_vertex;
    for (auto& vert : vertex) {
        transformed_vertex.emplace_back(transform * vert);
    }
    return transformed_vertex;
}

void Transform::transform(const glm::vec3& scale, const glm::vec3& rotate, 
        const glm::vec3& translate)
{
    glTranslatef(translate.x, translate.y, translate.z);
    glScalef(scale.x, scale.y, scale.z);
    glRotated(rotate.x, 1, 0, 0);
    glRotated(rotate.y, 0, 1, 0);
    glRotated(rotate.z, 0, 0, 1);
}

