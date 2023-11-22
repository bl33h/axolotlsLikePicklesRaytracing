#pragma once
#include "glm/glm.hpp"

class Camera {
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    float rotationSpeed;
    float zoomSpeed;

    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float rotationSpeed, float zoomSpeed);
    void zoom(float deltaZoom);
    void rotate(float deltaX, float deltaY);
    void move(float deltaZ);
    void processMouseScroll(float yOffset);
};