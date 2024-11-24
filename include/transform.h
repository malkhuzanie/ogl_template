#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <utils.h>

class Transform {
public:
    Transform();
    Transform(const glm::vec3& translate,
              const glm::vec3& scale = {1, 1, 1}, 
              const glm::vec3& rotate = {0, 0, 0}
            ); 

    static void transform(const glm::vec3& translate, const glm::vec3& scale, 
            const glm::vec3& rotate);

    std::vector<glm::vec4> transform(const std::vector<glm::vec4>&);

    bool changed = true;

    glm::vec3 translate;
    glm::vec3 rotate;
    glm::vec3 scale;
};

inline Transform operator+(Transform lhs, const Transform& rhs)
{
    lhs.translate += rhs.translate;
    lhs.scale *= rhs.scale;
    lhs.rotate += rhs.rotate;
    return lhs;
}

#endif
