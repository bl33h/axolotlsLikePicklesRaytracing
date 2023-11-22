/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: camera.h
@version: I
Creation: 07/11/2023
Last modification: 21/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/
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