#include "camera.h"
#include "glm/gtc/quaternion.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float rotationSpeed, float zoomSpeed)
    : position(position), target(target), up(up), rotationSpeed(rotationSpeed), zoomSpeed(zoomSpeed) {}

void Camera::zoom(float deltaZoom) {
    glm::vec3 dir = glm::normalize(target - position);
    position += dir * deltaZoom;
}

void Camera::processMouseScroll(float yOffset) {
    zoom(-yOffset * zoomSpeed);
}

void Camera::rotate(float deltaX, float deltaY) {
    glm::quat quatRotY = glm::angleAxis(glm::radians(deltaX * rotationSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat quatRotX = glm::angleAxis(glm::radians(deltaY * rotationSpeed), glm::vec3(1.0f, 0.0f, 0.0f));

    position = target + quatRotX * (position - target);
    position = target + quatRotY * (position - target);
}

void Camera::move(float deltaZ) {
    glm::vec3 dir = glm::normalize(target - position);
    position += dir * deltaZ;
}