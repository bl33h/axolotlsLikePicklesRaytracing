/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: camera.cpp
@version: I
Creation: 07/11/2023
Last modification: 21/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
#include "camera.h"
#include "glm/gtc/quaternion.hpp"

// constructor initializes camera with given position, target, up vector, rotation speed, and zoom speed
Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float rotationSpeed, float zoomSpeed)
    : position(position), target(target), up(up), rotationSpeed(rotationSpeed), zoomSpeed(zoomSpeed) {}

// zooms the camera based on the given deltaZoom value
void Camera::zoom(float deltaZoom) {
    // calculate the direction vector from camera position to target
    glm::vec3 dir = glm::normalize(target - position);
    // update camera position by moving along the direction vector
    position += dir * deltaZoom;
}

// processes mouse scroll input to adjust camera zoom
void Camera::processMouseScroll(float yOffset) {
    // delegate zooming operation with a scaled yOffset
    zoom(-yOffset * zoomSpeed);
}

// rotates the camera based on the given deltaX and deltaY values
void Camera::rotate(float deltaX, float deltaY) {
    // create quaternions for rotation around the Y and X axes
    glm::quat quatRotY = glm::angleAxis(glm::radians(deltaX * rotationSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat quatRotX = glm::angleAxis(glm::radians(deltaY * rotationSpeed), glm::vec3(1.0f, 0.0f, 0.0f));

    // update camera position by applying rotations
    position = target + quatRotX * (position - target);
    position = target + quatRotY * (position - target);
}

// moves the camera along its view direction based on the given deltaZ
void Camera::move(float deltaZ) {
    // calculate the direction vector from camera position to target
    glm::vec3 dir = glm::normalize(target - position);
    // update camera position by moving along the direction vector
    position += dir * deltaZ;
}