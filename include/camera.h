#include <utils.h>

enum DIRECTION {
    FORWARD, BACKWARD, LEFT, RIGHT
};

class Camera { 
public:
    Camera();

    void keyboard(const DIRECTION& direction);
    void mouse(const float xoffset, const float yoffset);
    void scroll(const float offset);
    void update();
    void set_view();

    glm::vec3 pos;
    glm::vec3 target;
    glm::vec3 up;
    glm::vec3 world_up;
    glm::vec3 right;

    float velocity;
    float yaw;
    float pitch;
    float fov;
};
