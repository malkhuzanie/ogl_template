#include <camera.h>

Camera::Camera()
    : pos {0, 0, 0},
      target {0, 0, -1},
      up {0, 1, 0},
      world_up {0, 1, 0}
{
    yaw = -90;
    fov = 45;
    pitch = 0;
    velocity = 7.5;
}

void Camera::set_view()
{
    glLoadIdentity();
    auto direction = pos + target;
    gluLookAt(pos.x, pos.y, pos.z,
              direction.x, direction.y, direction.z,
              up.x, up.y, up.z);
}

void Camera::update()
{
    target.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    target.y = sin(glm::radians(pitch));
    target.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    target   = glm::normalize(target);
    right    = glm::normalize(glm::cross(target, world_up));
    up       = glm::normalize(glm::cross(right, target));
}

void Camera::keyboard(const DIRECTION& direction) 
{
    switch (direction) 
    {
        case FORWARD:
            pos += velocity * target;
            break;
        case BACKWARD:
            pos -= velocity * target;
            break;
        case LEFT:
            pos -= glm::normalize(cross(target, up)) * velocity;
            break;
        case RIGHT:
            pos += glm::normalize(cross(target, up)) * velocity;
            break;
    }
}

void Camera::mouse(float xoffset, float yoffset)
{
    yaw   += xoffset * 0.1f;
    pitch += yoffset * 0.1f;
    if (pitch > 89.0f) {
        pitch = 89.0;
    } else if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    update();
}

void Camera::scroll(float offset)
{
    fov += offset;
    if (fov < 1) {
        fov = 1;
    } else if (fov > 45.0) {
        fov = 45;
    }
}
