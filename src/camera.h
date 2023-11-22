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
    // camera properties
    glm::vec3 position; //camera position in 3D space
    glm::vec3 target; // point the camera is looking at
    glm::vec3 up; // up vector for camera orientation

    // camera control parameters
    float rotationSpeed; // speed of rotation for camera
    float zoomSpeed; // speed of zooming for camera

    // constructor to initialize camera with position, target, up vector, rotation speed, and zoom speed
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float rotationSpeed, float zoomSpeed);

    // camera operations
    void zoom(float deltaZoom); // zoom the camera
    void rotate(float deltaX, float deltaY); // rotate the camera
    void move(float deltaZ); // move the camera
    void processMouseScroll(float yOffset); // process mouse scroll for zoom
};